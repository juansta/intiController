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

#include <eeprom.h>

/**
 * @brief The Settings class handles the reading and writting of configuration data
 * to the onboard EEPROM.
 */
class Settings
{
public:
    struct Emitters
    {
        uint8_t maxTotal;
        uint8_t maxWhite;
        uint8_t maxRoyalBlue;
        uint8_t maxBlue;
        uint8_t maxRed;
        uint8_t maxGreen;
        uint8_t maxYellow;
        uint8_t maxViolet;
    };

    struct Lcd
    {
        uint8_t maxRed;
        uint8_t maxGreen;
        uint8_t maxBlue;
    };

    Settings();
    ~Settings();

    bool setEmitters(const Emitters &values);
    const Emitters & getEmitters();

    bool setLcd(const Lcd &values);
    const Lcd & getLcd();
private:
    Emitters m_emitters;
    Lcd      m_lcd;

    static const uint8_t EMITTER_OFFSET = 0;
    static const uint8_t LCD_OFFSET     = 8;

    Eeprom m_eeprom;
};
