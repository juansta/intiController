
#include <avr/io.h>
#include <global.h>
#include <i2cmaster.h>
#include <string.h>
#include <inttypes.h>
#include <local_maths.h>
#include <delays.h>
#include <string.h>

#include "lcd.h"

// Class private constants and definition
const int     CMD_DELAY           = 1;  // Command delay in miliseconds
const int     CHAR_DELAY          = 0;  // Delay between characters in miliseconds
const int     PIXEL_ROWS_PER_CHAR = 8;  // Number of pixel rows in the LCD character
const int     MAX_USER_CHARS      = 16; // Maximun number of user defined characters

// LCD Command set
const uint8_t DISP_CMD       = 0x00; // Command for the display
const uint8_t RAM_WRITE_CMD  = 0x40; // Write to display RAM
const uint8_t CLEAR_DISP_CMD = 0x01; // Clear display command
const uint8_t HOME_CMD       = 0x02; // Set cursos at home (0,0)
const uint8_t DISP_ON_CMD    = 0x0C; // Display on command
const uint8_t DISP_OFF_CMD   = 0x08; // Display off Command
const uint8_t SET_DDRAM_CMD  = 0x80; // Set DDRAM address command
const uint8_t CONTRAST_CMD   = 0x70; // Set contrast LCD command
const uint8_t FUNC_SET_TBL0  = 0x38; // Function set - 8 bit, 2 line display 5x8, inst table 0
const uint8_t FUNC_SET_TBL1  = 0x39; // Function set - 8 bit, 2 line display 5x8, inst table 1

// LCD bitmap definition
const uint8_t CURSOR_ON_BIT  = ( 1 << 1 );// Cursor selection bit in Display on cmd.
const uint8_t BLINK_ON_BIT   = ( 1 << 0 );// Blink selection bit on Display on cmd.

// Driver DDRAM addressing
const uint8_t dram_dispAddr [][3] =
{
   { 0x00, 0x00, 0x00 },  // One line display address
   { 0x00, 0x40, 0x00 },  // Two line display address
   { 0x00, 0x10, 0x20 }   // Three line display address
};

Lcd::Lcd()
  : _num_lines    (2),
    _num_col      (20),
    _i2cAddress   (0x78),
    _cmdDelay     (CMD_DELAY),
    _charDelay    (CHAR_DELAY),
    _initialised  (false),
    _backlightPin (-1)
{
    init();
}

void Lcd::init ()
{
    i2c_init();
    i2c_start(_i2cAddress);
    i2c_write(DISP_CMD);
    i2c_write(FUNC_SET_TBL0);
    _delay_ms (10);
    i2c_write(FUNC_SET_TBL1);
    _delay_ms(10);
    i2c_write(0x14);  // Set BIAS - 1/5
    i2c_write(0x73);  // Set contrast low byte
    i2c_write(0x5E);  // ICON disp on, Booster on, Contrast high byte
    i2c_write(0x6D);  // Follower circuit (internal), amp ratio (6)
    i2c_write(0x0C);  // Display on
    i2c_write(0x01);  // Clear display
    i2c_write(0x06);  // Entry mode set - increment
    i2c_stop();

    _initialised = true;
}


void Lcd::setDelay (int cmdDelay,int charDelay)
{
    _cmdDelay = cmdDelay;
    _charDelay = charDelay;
}


void Lcd::command(uint8_t value)
{
    // If the LCD has been initialised correctly, write to it
    if (_initialised)
    {
        i2c_start(_i2cAddress);
        i2c_write(DISP_CMD);
        i2c_write(value);
        i2c_stop ();
        delay_ms(_cmdDelay);
    }
}


void Lcd::write(uint8_t value)
{
    // If the LCD has been initialised correctly write to it
    if (_initialised)
    {

        // If it is a new line, set the cursor to the next line (1,0)
        if (value == '\n')
            setCursor(1,0);
        else
        {
            i2c_start(_i2cAddress);
            i2c_write(RAM_WRITE_CMD);
            i2c_write(value);
            i2c_stop ();
            delay_ms(_charDelay);
        }
    }
}

void Lcd::write(const uint8_t *buffer, size_t size)
{
    // If the LCD has been initialised correctly, write to it
    if (_initialised)
    {
        i2c_start(_i2cAddress);
        i2c_write(RAM_WRITE_CMD);
        for (size_t i = 0; i < size; i++, buffer++)
            i2c_write(*buffer);
        i2c_stop();
        delay_ms(_charDelay);
    }
}
void Lcd::write(const uint8_t *buffer)
{
    // If the LCD has been initialised correctly, write to it
    if (_initialised)
    {
        uint8_t size = strlen((const char*)buffer);

        i2c_start(_i2cAddress);
        i2c_write(RAM_WRITE_CMD);
        for (size_t i = 0; i < size; i++, buffer++)
            i2c_write(*buffer);
        i2c_stop();
        delay_ms(_charDelay);
    }
}


void Lcd::clear()
{
    command(CLEAR_DISP_CMD);
}


void Lcd::home()
{
    command(HOME_CMD);
}


void Lcd::on()
{
    command(DISP_ON_CMD);
}


void Lcd::off()
{
    command(DISP_OFF_CMD);
}


void Lcd::cursor_on()
{
    command(DISP_ON_CMD | CURSOR_ON_BIT);
}

void Lcd::cursor_off()
{
    command(DISP_ON_CMD & ~(CURSOR_ON_BIT));
}

void Lcd::blink_on()
{
    command(DISP_ON_CMD | BLINK_ON_BIT);
}

void Lcd::blink_off()
{
    command(DISP_ON_CMD & ~(BLINK_ON_BIT));
}

void Lcd::setCursor(uint8_t line_num, uint8_t x)
{
    uint8_t base = 0x00;

    // If the LCD has been initialised correctly, write to it
    if (_initialised)
    {
        // set the baseline address with respect to the number of lines of
        // the display
        base = dram_dispAddr[_num_lines - 1][line_num];
        base = SET_DDRAM_CMD + base + x;
        command(base);
    }
}

uint8_t Lcd::status()
{
    return _status;
}

void Lcd::load_custom_character (uint8_t char_num, uint8_t *rows)
{
    // If the LCD has been initialised correctly start writing to it
    if (_initialised)
    {
        // If it is a valid place holder for the character, write it into the
        // display's CGRAM
        if (char_num < MAX_USER_CHARS)
        {
            // Set up the display to write into CGRAM - configure LCD to use func table 0
            i2c_start(_i2cAddress);
            i2c_write (DISP_CMD);
            i2c_write (FUNC_SET_TBL0); // Function set: 8 bit, 2 line display 5x8, funct tab 0
            delay_ms(_cmdDelay);

            // Set CGRAM position to write
            i2c_write (RAM_WRITE_CMD + (PIXEL_ROWS_PER_CHAR * char_num));
            i2c_stop ();

            // If we have changed the function table and configured the CGRAM position
            // write the new character to the LCD's CGRAM
            {
                write(rows, PIXEL_ROWS_PER_CHAR); // write the character to CGRAM

                // Leave the LCD as it was - function table 1 DDRAM and set the cursor
                // position to (0, 0) to start writing.
                command  (FUNC_SET_TBL1);
                setCursor(0,0);
            }
        }
    }
}


void Lcd::setBacklight(uint8_t new_val)
{
    // set backlight brightness
}

void Lcd::setRgb(uint8_t r,uint8_t g,uint8_t b)
{
    // set backlight colour
}

void Lcd::setContrast(uint8_t new_val)
{
    // Only allow 15 levels of contrast
    new_val = map ( new_val, 0, 255, 0, 15 );

    command(CONTRAST_CMD + new_val);
}
