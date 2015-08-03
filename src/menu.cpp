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
#include <rtc.h>

Menu::Menu()
: m_currentMenu(&Menu::showSplash)
{
    (this->*m_currentMenu)(FOCUS);
}

bool Menu::process(event newEvent)
{
    bool ret = false;
    menu_item old_menu = m_currentMenu;
    event_ret result = (this->*m_currentMenu)(newEvent);

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

// main level menu items
Menu::event_ret Menu::mainUnit(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("1. Unit Settings");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::setTime;
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::mainStatus;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::mainLights;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::mainLights(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("2. Emitter Settings");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::setMode;
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::mainUnit;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::mainStatus;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::mainStatus(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("3. Status");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::showSplash;
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::mainLights;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::mainUnit;
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

    switch (newEvent)
    {
        case FOCUS:
            {
                Rtc rtc;
                DateTime dt = rtc.now();
                m_lcd.clear();
                m_lcd.write("Set Unit Time");
                m_lcd.setCursor(1,0);
                m_lcd.write("%u/%02u/%02u %02u:%02u:%02u",
                        dt.year(), dt.month(), dt.day(),
                        dt.hour(), dt.minute(), dt.second());
                ret = HANDLED;
            }
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::settingTime;
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setTimeout;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setTimeZone;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setTimeZone(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Settings Timezone");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setTime;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setMimicZone;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::setMimicZone(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting MIMIC Zone");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setTimeZone;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setLcd;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setLcd (event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Set LCD Setting");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setMimicZone;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setTimeout;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::setTimeout(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting Timeout");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setLcd;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::unitExit;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::unitExit(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Exit");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::mainUnit;
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setTimeout;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setTime;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setMode(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting Mode");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setVMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::setMax(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting Max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setMode;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setWMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setWMax(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting WHITE max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setBMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::setBMax(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Set BLUE max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setWMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setRBMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setRBMax(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Set ROYAL BLUE max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setBMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setRMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::setRMax(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting RED max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setRBMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setGMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setGMax(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting GREEN max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setRMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setYMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::setYMax(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting YELLOW max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setGMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setVMax;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setVMax(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Setting UV max");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setYMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::lightExit;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::lightExit(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Exit");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::mainLights;
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setVMax;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::setMode;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
    return ret;
}
Menu::event_ret Menu::showSplash(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            {
                Rtc rtc;
                rtc.setCharger(2);
                DateTime dt = rtc.now();

                m_lcd.clear();
                m_lcd.setCursor(0,0);
                m_lcd.write("%u/%02u/%02u %02u:%02u:%02u", dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
                m_lcd.setCursor(1,0);
                m_lcd.write("%s", LONG_VERSION);
                ret = HANDLED;
            }
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::statusExit;
            ret = HANDLED;
            break;

        case UP:
            m_currentMenu = &Menu::statusExit;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::statusExit(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Exit");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::mainStatus;
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::showSplash;
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
Menu::event_ret Menu::settingTime(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            ret = HANDLED;
            break;

        case UP:
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::settingTimeZone(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            ret = HANDLED;
            break;

        case UP:
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::settingMimicTimeZone(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            ret = HANDLED;
            break;

        case UP:
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::settingLcd(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            ret = HANDLED;
            break;

        case UP:
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
Menu::event_ret Menu::settingTimeout(event newEvent)
{
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            ret = HANDLED;
            break;

        case DOWN:
            ret = HANDLED;
            break;

        case UP:
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }

    return ret;
}
