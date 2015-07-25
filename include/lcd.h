#pragma once

// define for advance functions
#define _LCDEXPANDED

#include <stdlib.h>
#include <inttypes.h>
#include "lcd.h"

#define _ST7036_VERSION       "1.0"
#define _LCD_API_VERSION      "1.0"

class Lcd
{
public:

   /**
    @brief Constructor for the display class

    @param num_lines[in] Number of lines in the display
    @param num_col[in]   Number of columns in the display
    @param i2cAddr[in]   i2c address of the display

    @return None
    */
   Lcd();

   /**
    Send a command to the display

    @param value[in] Command to be sent to the display

    @return None
    */
    void command(uint8_t value);

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

    /**
    Set a different delay to that in the library. It may be needed to delay
    sending commands or characters one after the other.

    @param cmdDelay[in] Delay after issuing a command
    @param charDelay[in] Delay after issuing a character to the LCD

    @return None

    void setDelay(int,int);
    */
    void setDelay(int,int);

   /**
    This is the write method used by the Print library. It allows printing
    characters to the display and new lines: print, println. It will write the
    value to the display and increase the cursor.

    @param value[in] character to write to the current LCD write position

    @return None

    virtual void write(uint8_t);
    */
    virtual void write(uint8_t);

   /**
    This is the write method used by the Print library. It allows printing
    characters to the display and new lines: print, println. It will write the
    value to the display and increase the cursor.

    @param buffer[in] buffer to write to the current LCD write position

    @return None

    virtual void write(uint8_t, size_t);
    */
   void write(const uint8_t *buffer, size_t size);
   void write(const uint8_t *buffer);

   /**
    Clear the display and set the cursor to 0,0

    void clear();
    */
    void clear();

   /**
    Set the cursor to 0,0

    void home();
    */
    void home();

   /**
    Switch the display on. This is the default state when the display is
    initialised. See. init() method

    void on();
    */
    void on();

   /**
    Switch the display off.

    void off();
    */
    virtual void off();

   /**
    Turn on the cursor "_".

    void cursor_on();
    */
    void cursor_on();

   /**
    Turn off the cursor. This is the default state when the display is
    initialised.

    void cursor_off();
    */
    void cursor_off();

   /**
    Activate cursor blink.

    void blink_on();
    */
    void blink_on();

   /**
    Deactivate cursor blinking. This is the default state when the display is
    initialised.

    void blink_off ();
    */
    void blink_off();

   /**
    Set the cursor at the following coordinates (Line, Col). Initial value after
    initialization is (0,0).

    @param Line[in] Line where to put the cursor, range (0, max display lines-1)
    This display only take (0, 1)
    @param Col[in]  Colum where to put the cursor, range (0, max width+1)

    @return None

    void setCursor(uint8_t Line, uint8_t Col );
    */
    void setCursor(uint8_t Line, uint8_t Col );

    //
   // EXPANDED FUNCTIONALITY METHODS
   // --------------------------------------------------------------------------

#ifdef _LCDEXPANDED

    /**
    Provides the state of the LCD. This value is updated every command is sent
    to the LCD or a character or a buffer is writen to the display.

    @return 0 OK, 1 if data was too big to be transmitted, 2 NACK on address
    transmission, 3 NACK on data transmission, 4 other error.

    uint8_t status();
    */
    uint8_t status();

   /**
    Load a custom character on the display. After adding a new character to
    the character set, the coordinates are set to (0, 0). This method should
    be called during initialization.

    @param char_num[in] Character to load onto the display, this display supports
    upto 16 user defined characters.
    @param rows[in] Bitmap defining the character, the display assumes an array
    of 8 bytes per character.

    @return None.

    uint8_t load_custom_character(uint8_t char_num, uint8_t *rows);
    */
    void load_custom_character(uint8_t char_num, uint8_t *rows);

    /**
    NOT SUPPORTED

    uint8_t keypad();
    */
    uint8_t keypad();

    void printstr(const char[]);

   /**
    Sets the backlight level. If the backlight level is connected to a PWM  pin,
    new_val will set a light level range between 0 and 255. If it is connected
    to a normal GPIO, from 0 to 127 it will be off and from 128 to 255 the
    backlight will be on. Backlight pin allocation on constructor.

    @param new_val[in] Backlight level of the display. Full range will only be
    available on pins with PWM support.

    @return None.

    uint8_t setBacklight();
    */
    void setBacklight(uint8_t new_val);

    void setRgb(uint8_t, uint8_t, uint8_t);
   /**
    Sets the LCD contrast level.

    @param new_val[in] The contrast range (0 to 255) has been mapped to 16
    contrast levels on the display.

    @return None.

    uint8_t setContrast();
    */
    void setContrast(uint8_t new_val);

#endif

private:
    uint8_t _num_lines;
    uint8_t _num_col;
    uint8_t _i2cAddress;
    int     _cmdDelay;
    int     _charDelay;
    bool    _initialised;
    uint8_t _status;
    int8_t  _backlightPin;
};
