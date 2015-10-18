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

#include <inttypes.h>
#include <dimmer.h>

class Led
{
public:
    enum eMode    {UP, DOWN, STEADY};
    enum eChannel {WHITE, ROYAL_BLUE, BLUE, RED, GREEN, VIOLET, YELLOW};
    Led();

    void disable();
    void enable ();

    void setMode(eChannel channel, eMode mode, uint16_t delay = 0);

    void tick();

private:
    class Channel
    {
        public:
            Dimmer * dimmer;
            eMode    mode;
            uint16_t delay;
    } ;

    Channel m_dimmers[7];
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
