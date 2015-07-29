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

#include <menu.h>
#include <revision>

Menu::Menu()
: m_currentMenu(&Menu::showSplash)
{
    (this->*m_currentMenu)(FOCUS);
}

bool Menu::process(event _event)
{
    bool ret = false;
    menu_item old_menu = m_currentMenu;
    event_ret result = (this->*m_currentMenu)(_event);

    if (m_currentMenu != old_menu)
        ret = process(FOCUS);
    else
    {
        switch (result)
        {
        case ERROR:
            ret = false;
            break;

        default:
            ret = true;
            break;
        }
    }

    return ret;
}

Menu::event_ret Menu::showSplash(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.setCursor(0,0);
            m_lcd.write("showSplash");
            m_lcd.setCursor(1,0);
            m_lcd.write("%s", LONG_VERSION);
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::showTemperature;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::showTime;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::showTime(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("showTime");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::showSplash;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::showTemperature;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::showTemperature(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("showTemperature");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::showTime;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::showSplash;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::setTime(event newEvent)
{
    event_ret ret = ERROR;

    return ret;
}
Menu::event_ret Menu::setLcd (event newEvent)
{
    event_ret ret = ERROR;

    return ret;
}
