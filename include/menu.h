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

#include <lcd.h>

class Menu
{
    public:
        enum event {NOTHING = 0, FOCUS, TICK, CLICK, DOWN, UP};

    Menu();

    bool process(event _event);

private:
    // returned values from state machine
    enum event_ret {HANDLED, NOT_HANDLED, ERROR };

    // function pointer definition
    typedef event_ret (Menu::*menu_item)(event) ;
    menu_item m_currentMenu;

    uint8_t   m_timeOut;

    // display output
    Lcd m_lcd;

    // main level menu items
    event_ret mainUnit(event);
    event_ret mainLights(event);
    event_ret mainStatus(event);

    // menu items that appear under the "unit" heading
    event_ret setTime(event);
    event_ret setTimeZone(event);
    event_ret setMimicZone(event);
    event_ret setLcd (event);
    event_ret setTimeout(event);
    event_ret unitExit(event);

    // menu items that appear under the "lights" heading
    event_ret setMode(event);
    event_ret setMax(event);
    event_ret setWMax(event);
    event_ret setBMax(event);
    event_ret setRBMax(event);
    event_ret setRMax(event);
    event_ret setGMax(event);
    event_ret setYMax(event);
    event_ret setVMax(event);
    event_ret lightExit(event);

    // menu items that appear unde the "status" heading
    event_ret showTime(event);
    event_ret showTemperature(event);
    event_ret showSplash(event);
    event_ret showExit(event);
};
