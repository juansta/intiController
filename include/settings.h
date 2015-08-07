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
    Settings();
    ~Settings();

    bool commit();

    bool setMaxTotal(uint8_t);
    bool setMaxW(uint8_t);
    bool setMaxRB(uint8_t);
    bool setMaxB(uint8_t);
    bool setMaxR(uint8_t);
    bool setMaxG(uint8_t);
    bool setMaxY(uint8_t);
    bool setMaxV(uint8_t);

    bool getMaxTotal(uint8_t&);
    bool getMaxW(uint8_t&);
    bool getMaxRB(uint8_t&);
    bool getMaxB(uint8_t&);
    bool getMaxR(uint8_t&);
    bool getMaxG(uint8_t&);
    bool getMaxY(uint8_t&);
    bool getMaxV(uint8_t&);

private:
    /**
     * @brief The Configuration struct
     */
    struct Configuration
    {
        uint8_t maxTotal;
        uint8_t maxW;
        uint8_t maxRB;
        uint8_t maxB;
        uint8_t maxR;
        uint8_t maxG;
        uint8_t maxY;
        uint8_t maxV;
    } m_config;

    Eeprom m_eeprom;
};
