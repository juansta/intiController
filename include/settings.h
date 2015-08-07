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
