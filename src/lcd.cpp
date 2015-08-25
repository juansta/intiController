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


#include <avr/io.h>
#include <global.h>
#include <i2cmaster.h>
#include <string.h>
#include <inttypes.h>
#include <local_maths.h>
#include <delays.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "lcd.h"

// Driver DDRAM addressing
const uint8_t dram_dispAddr [][3] =
{
   { 0x00, 0x00, 0x00 },  // One line display address
   { 0x00, 0x40, 0x00 },  // Two line display address
   { 0x00, 0x10, 0x20 }   // Three line display address
};

Lcd::Lcd()
  : m_num_lines    (2),
    m_num_col      (20),
    m_i2cAddress   (0x78),
    m_cmdDelay     (CMD_DELAY),
    m_charDelay    (CHAR_DELAY),
    m_red          (0),
    m_green        (0),
    m_blue         (0)
{
    init();
}

void Lcd::init ()
{
    i2c_init();
    i2c_start(m_i2cAddress);
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
}


void Lcd::setDelay (int cmdDelay,int charDelay)
{
    m_cmdDelay = cmdDelay;
    m_charDelay = charDelay;
}


void Lcd::command(uint8_t value)
{
    i2c_start(m_i2cAddress);
    i2c_write(DISP_CMD);
    i2c_write(value);
    i2c_stop ();
    delay_ms (m_cmdDelay);
}


void Lcd::write(uint8_t value)
{
    // If it is a new line, set the cursor to the next line (1,0)
    if (value == '\n')
        setCursor(1,0);
    else
    {
        i2c_start(m_i2cAddress);
        i2c_write(RAM_WRITE_CMD);
        i2c_write(value);
        i2c_stop ();
        delay_ms (m_charDelay);
    }
}

void Lcd::write(const uint8_t *buffer, size_t size)
{
    i2c_start(m_i2cAddress);
    i2c_write(RAM_WRITE_CMD);
    for (size_t i = 0; i < size; i++, buffer++)
        i2c_write(*buffer);
    i2c_stop();
}

void Lcd::write(const char *buffer, ...)
{
    char    msg_buf[40];
    va_list ap;
    va_start(ap, buffer);
    int n = vsnprintf(msg_buf, 40, buffer, ap);

    i2c_start(m_i2cAddress);
    i2c_write(RAM_WRITE_CMD);
    for (uint8_t i = 0; i < n; i++)
        i2c_write(msg_buf[i]);
    i2c_stop();

    va_end(ap);
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

    // set the baseline address with respect to the number of lines of
    // the display
    base = dram_dispAddr[m_num_lines - 1][line_num];
    base = SET_DDRAM_CMD + base + x;
    command(base);
}

void Lcd::load_custom_character (uint8_t char_num, uint8_t *rows)
{
    // If it is a valid place holder for the character, write it into the
    // display's CGRAM
    if (char_num < MAX_USER_CHARS)
    {
        // Set up the display to write into CGRAM - configure LCD to use func table 0
        i2c_start(m_i2cAddress);
        i2c_write (DISP_CMD);
        i2c_write (FUNC_SET_TBL0); // Function set: 8 bit, 2 line display 5x8, funct tab 0
        delay_ms(m_cmdDelay);

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

void Lcd::backlight_on()
{}
void Lcd::backlight_off()
{}
void Lcd::getRgb(uint8_t&red, uint8_t&green, uint8_t&blue)
{
    red   = m_red;
    green = m_green;
    blue  = m_blue;
}
void Lcd::setRgb(uint8_t r,uint8_t g,uint8_t b)
{
    // configure HW PWM

    // store new values to eeprom
}

void Lcd::setContrast(uint8_t new_val)
{
    // Only allow 15 levels of contrast
    new_val = map ( new_val, 0, 255, 0, 15 );

    command(CONTRAST_CMD + new_val);
}
