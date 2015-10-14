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
#include <led.h>
#include <datetime.h>

class Controller
{
public:
    enum eMode {AUTO, MANUAL};
    Controller();

    void setMode(eMode mode);

    void newTime(const DateTime & currTime);
    void tick();

    void setWhite (const uint16_t & white);
    void setRBlue (const uint16_t & rblue);
    void setBlue  (const uint16_t & blue);
    void setRed   (const uint16_t & red);
    void setGreen (const uint16_t & green);
    void setViolet(const uint16_t & violet);
    void setAmber (const uint16_t & amber);

private:
    eMode    m_mode;
    DateTime m_sunrise;
    DateTime m_sunset;
    uint16_t m_delay;
    Led      m_leds;
};
