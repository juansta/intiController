#include "lcd.h"

// Class private constants and definition
// ----------------------------------------------------------------------------
const int     NUM_LINES           = 2;     // Number of lines in the display
const int     NUM_COLUMNS         = 20;    // Number of columns in the display
const int     I2C_ADDRS           = 0x78;  // I2C address of the display

Lcd::Lcd()
    : ST7036 (NUM_LINES, NUM_COLUMNS, I2C_ADDRS)
{
}
