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

#pragma once

// define for advance functions
#define _LCDEXPANDED

#include <stdlib.h>
#include <inttypes.h>
#include <dimmer.h>

class Lcd
{
public:

    Lcd();

    void command(uint8_t value);

    void setDelay(int,int);

    virtual void write(uint8_t);
    void write(const uint8_t *buffer, size_t size);
    void write(const char *buffer, ...);

    void clear();

    void home();

    void on();
    virtual void off();

    void cursor_on();
    void cursor_off();

    void blink_on();
    void blink_off();

    void setCursor(uint8_t Line, uint8_t Col );

    void load_custom_character(uint8_t char_num, uint8_t *rows);

    void backlight_on();
    void backlight_off();

    void getRgb(uint16_t &red, uint16_t &green, uint16_t &blue);
    void setRgb(const uint16_t &red, const uint16_t &green, const uint16_t &blue);

    void setContrast(uint8_t new_val);

private:
    /**
     Initialise the display. Once created the object, this is the next operation
     that has to be called to initialise the display into a known state. It
     assumes that the I2C bus is not initialised and hence initialise the Wire
     interface.

     Clear the display
     Set contrast levels
     Set the cursor at origens (0,0)
     Turn on the entire display

     void init();
     */
     void init();

    uint8_t m_num_lines;
    uint8_t m_num_col;
    uint8_t m_i2cAddress;
    int     m_cmdDelay;
    int     m_charDelay;

    // Class private constants and definition
    static const int     CMD_DELAY           = 1;  // Command delay in miliseconds
    static const int     CHAR_DELAY          = 0;  // Delay between characters in miliseconds
    static const int     PIXEL_ROWS_PER_CHAR = 8;  // Number of pixel rows in the LCD character
    static const int     MAX_USER_CHARS      = 16; // Maximun number of user defined characters

    // LCD Command set
    static const uint8_t DISP_CMD       = 0x00; // Command for the display
    static const uint8_t RAM_WRITE_CMD  = 0x40; // Write to display RAM
    static const uint8_t CLEAR_DISP_CMD = 0x01; // Clear display command
    static const uint8_t HOME_CMD       = 0x02; // Set cursos at home (0,0)
    static const uint8_t DISP_ON_CMD    = 0x0C; // Display on command
    static const uint8_t DISP_OFF_CMD   = 0x08; // Display off Command
    static const uint8_t SET_DDRAM_CMD  = 0x80; // Set DDRAM address command
    static const uint8_t CONTRAST_CMD   = 0x70; // Set contrast LCD command
    static const uint8_t FUNC_SET_TBL0  = 0x38; // Function set - 8 bit, 2 line display 5x8, inst table 0
    static const uint8_t FUNC_SET_TBL1  = 0x39; // Function set - 8 bit, 2 line display 5x8, inst table 1

    // LCD bitmap definition
    static const uint8_t CURSOR_ON_BIT  = ( 1 << 1 );// Cursor selection bit in Display on cmd.
    static const uint8_t BLINK_ON_BIT   = ( 1 << 0 );// Blink selection bit on Display on cmd.

    // LCD backlight controllers
    Dimmer m_red;
    Dimmer m_green;
    Dimmer m_blue;

    uint16_t    m_oldRed;
    uint16_t    m_oldGreen;
    uint16_t    m_oldBlue;

    bool m_blon;
};
