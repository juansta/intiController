// A library for handling real-time clocks, dates, etc.
// 2010-02-04 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php
// 2012-11-08 RAM methods - idreammicro.com
// 2012-11-14 SQW/OUT methods - idreammicro.com

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <global.h>
#include <i2cmaster.h>
#include <avr/pgmspace.h>
#include "rtc.h"

#define BQ32000_ADDRESS         0xD0
#define READ                    0x01
#define WRITE                   0x00
// BQ32000 register addresses:
#define BQ32000_CAL_CFG1        0x07
#define BQ32000_TCH2            0x08
#define BQ32000_CFG2            0x09
#define BQ32000_SFKEY1          0x20
#define BQ32000_SFKEY2          0x21
#define BQ32000_SFR             0x22
// BQ32000 config bits:
#define BQ32000__OUT            0x07 // CAL_CFG1 - IRQ active state
#define BQ32000__FT             0x06 // CAL_CFG1 - IRQ square wave enable
#define BQ32000__CAL_S          0x05 // CAL_CFG1 - Calibration sign
#define BQ32000__TCH2_BIT       0x05 // TCH2 - Trickle charger switch 2
#define BQ32000__TCFE           0x06 // CFG2 - Trickle FET control
// BQ32000 config values:
#define BQ32000_CHARGE_ENABLE   0x05 // CFG2 - Trickle charger switch 1 enable
#define BQ32000_SFKEY1_VAL      0x5E
#define BQ32000_SFKEY2_VAL      0xC7
#define BQ32000_FTF_1HZ         0x01
#define BQ32000_FTF_512HZ       0x00

#define SECONDS_PER_DAY         86400L


static const uint8_t daysInMonth [] PROGMEM = {
  31,28,31,30,31,30,31,31,30,31,30,31
};

// number of days since 2000/01/01, valid for 2001..2099
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    if (m > 2 && y % 4 == 0)
        ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}

////////////////////////////////////////////////////////////////////////////////
// DateTime implementation - ignores time zones and DST changes
// NOTE: also ignores leap seconds, see http://en.wikipedia.org/wiki/Leap_second

DateTime::DateTime (long t) {
    ss = t % 60;
    t /= 60;
    mm = t % 60;
    t /= 60;
    hh = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;
    for (yOff = 0; ; ++yOff) {
        leap = yOff % 4 == 0;
        if (days < 365 + leap)
            break;
        days -= 365 + leap;
    }
    for (m = 1; ; ++m) {
        uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
        if (leap && m == 2)
            ++daysPerMonth;
        if (days < daysPerMonth)
            break;
        days -= daysPerMonth;
    }
    d = days + 1;
}

DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000)
        year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

static uint8_t conv2d(const char* p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

// A convenient constructor for using "the compiler's time":
//   DateTime now (__DATE__, __TIME__);
// NOTE: using PSTR would further reduce the RAM footprint
DateTime::DateTime (const char* date, const char* time) {
    // sample input: date = "Dec 26 2009", time = "12:34:56"
    yOff = conv2d(date + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
    switch (date[0]) {
        case 'J': m = date[1] == 'a' ? 1 : m = date[2] == 'n' ? 6 : 7; break;
        case 'F': m = 2; break;
        case 'A': m = date[2] == 'r' ? 4 : 8; break;
        case 'M': m = date[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }
    d = conv2d(date + 4);
    hh = conv2d(time);
    mm = conv2d(time + 3);
    ss = conv2d(time + 6);
}

uint8_t DateTime::dayOfWeek() const {
    uint16_t day = get() / SECONDS_PER_DAY;
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

long DateTime::get() const {
    uint16_t days = date2days(yOff, m, d);
    return time2long(days, hh, mm, ss);
}

volatile bool ticked = false;

ISR(PCINT1_vect)
{
    ticked = PINC & (1 << PC2);
}
Rtc::Rtc()
{
    i2c_init();
    setCharger(2);
    setIRQ(1);

    DDRC   &= ~(1 << PC2);
    PORTC  |=  (1 << PC2);

    PCMSK1 |= (1 << PCINT11); // push button
    PCICR  |= (1 << PCIE1);
}
Rtc::~Rtc()
{}
bool Rtc::tick()
{
    bool ret = ticked;
    ticked = false;
     return ret;
}
void Rtc::adjust(const DateTime& dt)
{
    if (i2c_start(BQ32000_ADDRESS | WRITE))
    {
        if (i2c_write(0))
        {
            i2c_write(bin2bcd(dt.second()));
            i2c_write(bin2bcd(dt.minute()));
            i2c_write(bin2bcd(dt.hour()));
            i2c_write(bin2bcd(0));
            i2c_write(bin2bcd(dt.day()));
            i2c_write(bin2bcd(dt.month()));
            i2c_write(bin2bcd(dt.year() - 2000));
            i2c_stop();
        }
    }
}
DateTime Rtc::now()
{
    uint8_t ss = 0;
    uint8_t mm = 0;
    uint8_t hh = 0;
    uint8_t d  = 0;
    uint8_t m  = 0;
    uint16_t y = 0;

    i2c_start(BQ32000_ADDRESS | WRITE);

    if (i2c_write(0))
    {
        i2c_rep_start(BQ32000_ADDRESS | READ);

        ss = bcd2bin(i2c_read(false));
        mm = bcd2bin(i2c_read(false));
        hh = bcd2bin(i2c_read(false));
        d  = bcd2bin(i2c_read(false));
        m  = bcd2bin(i2c_read(false));
        y  = bcd2bin(i2c_read(true)) + 2000;

        i2c_stop();
    }

    return DateTime (y, m, d, hh, mm, ss);
}

void Rtc::setIRQ(uint8_t state)
{
    // Set IRQ square wave output state: 0=disabled, 1=1Hz, 2=512Hz.
    if (state)
    {
        // Setting the frequency is a bit complicated on the BQ32000:
        if (i2c_start(BQ32000_ADDRESS | WRITE))
        {
            i2c_write(BQ32000_SFKEY1);
            i2c_write(BQ32000_SFKEY1_VAL);
            i2c_write(BQ32000_SFKEY2_VAL);
            i2c_write((state == 1) ? BQ32000_FTF_1HZ : BQ32000_FTF_512HZ);
            i2c_stop();
        }
    }

    uint8_t value = readRegister(BQ32000_CAL_CFG1);
    value = (!state) ? value & ~(1<<BQ32000__FT) : value | (1<<BQ32000__FT);
    writeRegister(BQ32000_CAL_CFG1, value);
}

void Rtc::setIRQLevel(uint8_t level)
{
    // The IRQ active level bit is in the same register as the calibration
    // settings, so we preserve its current state:
    uint8_t value = readRegister(BQ32000_CAL_CFG1);
    value = (!level) ? value & ~(1<<BQ32000__OUT) : value | (1<<BQ32000__OUT);
    writeRegister(BQ32000_CAL_CFG1, value);
}

void Rtc::setCalibration(int8_t value)
{
    // Sets the calibration value to given value in the range -31 - 31, which
    // corresponds to -126ppm - +63ppm; see table 13 in th BQ32000 datasheet.
    if (value > 31) value = 31;
    if (value < -31) value = -31;
    uint8_t val = (uint8_t) (value < 0) ? -value | (1<<BQ32000__CAL_S) : value;
    val |= readRegister(BQ32000_CAL_CFG1) & ~0x3f;
    writeRegister(BQ32000_CAL_CFG1, val);
}

void Rtc::setCharger(int state)
{
    /* If using a super capacitor instead of a battery for backup power, use this
     * method to set the state of the trickle charger: 0=disabled, 1=low-voltage
     * charge, 2=high-voltage charge. In low-voltage charge mode, the super cap is
     * charged through a diode with a voltage drop of about 0.5V, so it will charge
     * up to VCC-0.5V. In high-voltage charge mode the diode is bypassed and the super
     * cap will be charged up to VCC (make sure the charge voltage does not exceed your
     * super cap's voltage rating!!).
     */
    // First disable charger regardless of state (prevents it from
    // possible starting up in the high voltage mode when the low
    // voltage mode is requested):
    uint8_t value;
    writeRegister(BQ32000_TCH2, 0);
    if (state <= 0 || state > 2) return;
    value = BQ32000_CHARGE_ENABLE;
    if (state == 2) {
        // High voltage charge enable:
        value |= (1 << BQ32000__TCFE);
    }
    writeRegister(BQ32000_CFG2, value);
    // Now enable charger:
    writeRegister(BQ32000_TCH2, 1 << BQ32000__TCH2_BIT);
}


uint8_t Rtc::readRegister(uint8_t address)
{
    uint8_t ret = 0;

    if (i2c_start(BQ32000_ADDRESS | WRITE))
    {
        i2c_write(address);
        i2c_rep_start(BQ32000_ADDRESS | READ);

        ret = i2c_read(true);
        i2c_stop();
    }

    return ret;
}

bool Rtc::writeRegister(uint8_t address, uint8_t * values, uint8_t len)
{
    bool ret = false;

    if (i2c_start(BQ32000_ADDRESS | WRITE))
    {
        uint8_t written = 0;
        i2c_write(address);
        while (written < len && i2c_write(*values++))
            written++;

        i2c_stop();

        ret = (written == len);
    }

    return ret;
}
bool Rtc::writeRegister(uint8_t address, uint8_t value)
{
    bool ret = false;

    if (i2c_start(BQ32000_ADDRESS | WRITE))
    {
        i2c_write(address);
        ret = i2c_write(value);
        i2c_stop();
    }

    return ret;
}

uint8_t Rtc::isrunning()
{
    return !(readRegister(0x0)>>7);
}
