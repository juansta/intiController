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
 * Original file built from https://github.com/jcw/rtclib
 *
 */

#pragma once

#include <inttypes.h>
#include <dimmer.h>

class Led
{
public:
    Led();

    void newConfiguration();


private:
    static const uint8_t WHITE      = 0;
    static const uint8_t ROYAL_BLUE = 1;
    static const uint8_t BLUE       = 2;
    static const uint8_t RED        = 3;
    static const uint8_t GREEN      = 4;
    static const uint8_t VIOLET     = 5;
    static const uint8_t YELLOW     = 6;
    static const uint8_t TOTAL      = 7;

    // need to be seperate (no container)
    // due to avr-gcc limitation(s)
    // fair enough as embedded, declare all memory
    // upfront
    Dimmer m_white;
    Dimmer m_rblue;
    Dimmer m_blue;
    Dimmer m_red;
    Dimmer m_green;
    Dimmer m_violet;
    Dimmer m_yellow;

};
