/*
 * This file is part of intiLED.
 *
 * intiLED is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * intiLED is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with intiLED.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <delays.h>
#include <dimmer.h>
#include <i2cmaster.h>

Dimmer::Dimmer()
{
    i2c_init();

    write(MODE1, MODE1_AUTOINC);
    write(MODE2, MODE2_OCH | MODE2_LEDnHighZ);

    setFrequency(200);
}
Dimmer::~Dimmer()
{}
void Dimmer::setLcd(uint16_t r, uint16_t g, uint16_t b)
{}
void Dimmer::setWhite(uint8_t w)
{}
void Dimmer::setRoyalBlue(uint8_t rb)
{}
void Dimmer::setBlue(uint8_t b)
{}
void Dimmer::setGreen(uint8_t w)
{}
void Dimmer::setRed(uint8_t w)
{}
void Dimmer::setYellow(uint8_t w)
{}
void Dimmer::setFrequency(float freq)
{
    float prescaleval = 25000000;

    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;

    uint8_t prescale = floor(prescaleval + 0.5);

    uint8_t oldmode = read(MODE1);
    uint8_t newmode = (oldmode & 0x7F) | 0x10; // sleep

    write(MODE1, newmode);             // go to sleep
    write(PCA9685_PRESCALE, prescale); // set the prescaler
    write(MODE1, oldmode);

    delay_ms(5);

    write(MODE1, oldmode | 0xa1);
}

uint8_t Dimmer::read(uint8_t addr)
{
    uint8_t ret = 0;

    if (i2c_start(PCA9685 | READ))
    {
        if (i2c_rep_start(addr))
            ret = i2c_read(true);

        i2c_stop();
    }

    return ret;
}

void Dimmer::write(uint8_t addr, uint8_t d)
{
    if (i2c_start(PCA9685 | WRITE))
    {
        i2c_write(addr);
        i2c_write(d);

        i2c_stop();
    }
}
