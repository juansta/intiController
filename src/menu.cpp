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
#include <settings.h>


void showrgb(Lcd& lcd, uint8_t offset, uint8_t*vals)
{
    lcd.setCursor(1,0);
    lcd.write("R - %2u G - %2u B - %2u", vals[0], vals[1], vals[2]);

    lcd.setCursor(1, offset);
}

Menu::Menu()
: m_currentMenu(&Menu::showSplash),
  m_timeOutLen (120),
  m_timeOut    (0)
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
        m_lcd.clear();
        m_lcd.write("Set Unit Time");
    }
    case TICK:
    {
        DateTime dt = Rtc::now();
        m_lcd.setCursor(1,0);
        m_lcd.write("%u/%02u/%02u %02u:%02u:%02u",
                    dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
        ret = HANDLED;
        break;
    }

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
        {
            Settings setting;
            const Settings::Lcd lcd = setting.getLcd();
            m_lcd.clear();
            m_lcd.write("Set LCD Setting");
            showrgb(m_lcd, 0, (uint8_t*)&lcd);
            ret = HANDLED;
            break;
        }
        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            m_currentMenu = &Menu::settingLcd;
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
            m_lcd.write("Set Timeout");
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
            m_currentMenu = &Menu::setBootloader;
            ret = HANDLED;
            break;

        case NOTHING:
        default:
            ret = NOT_HANDLED;
            break;
    }
     return ret;
}
Menu::event_ret Menu::setBootloader(event newEvent)
{
     event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
            m_lcd.clear();
            m_lcd.write("Bootload");
            ret = HANDLED;
            break;

        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            // reset program vector to DFU bootloader
            ret = HANDLED;
            break;

        case DOWN:
            m_currentMenu = &Menu::setTimeout;
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
    static uint8_t page = 0;
    event_ret ret = ERROR;

    switch (newEvent)
    {
        case FOCUS:
        {
            ret = (this->*m_currentMenu)(TICK);
        }
        break;

        case TICK:
        switch (page)
        {
        case 0:
            {
                DateTime dt = Rtc::now();

                m_lcd.clear();
                m_lcd.setCursor(0,0);
                m_lcd.write("%u/%02u/%02u %02u:%02u:%02u", dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
                m_lcd.setCursor(1,0);
                m_lcd.write("%s", LONG_VERSION);
            }
        }
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
uint8_t Menu::increment(uint8_t value, int8_t inc, uint8_t max)
{
    return (value + inc) % max;
}
Menu::event_ret Menu::settingTime(event newEvent)
{
    static uint8_t loc       =  0;
    static uint8_t values[6] = { 0,  0,  0,  0,  0,  0};
           uint8_t offset[6] = { 3,  6,  9, 12, 15, 18};
           uint8_t maxval[6] = {99, 12, 31, 23, 59, 59};

    event_ret ret = ERROR;

    switch (newEvent)
    {
    case FOCUS:
    {
        loc = 0;
        DateTime dt  = Rtc::now();
        m_lcd.clear();
        m_lcd.write("Update Time");

        m_lcd.setCursor(1,0);
        m_lcd.write("%u/%02u/%02u %02u:%02u:%02u",
                    dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());

        values[5] = dt.second();
        values[4] = dt.minute();
        values[3] = dt.hour();
        values[2] = dt.day();
        values[1] = dt.month();
        values[0] = dt.shortyear();

        m_lcd.setCursor(1, 3);
        m_lcd.blink_on();

        ret = HANDLED;
        break;
    }

    case TICK:
    {
        // we dont really care about the ticker when setting the time
        ret = HANDLED;
        break;
    }

    case CLICK:
    {
        // go to next loc/item until all items are entered
        if (++loc < 6)
        {
            m_lcd.setCursor(1, offset[loc]);
            m_lcd.blink_on();
        }
        else
        {
            DateTime newTime(values[0] + 2000, values[1], values[2],
                    values[3], values[4], values[5]);
            Rtc::adjust(newTime);
            m_lcd.blink_off();

            m_currentMenu = &Menu::setTime;
        }
        ret = HANDLED;
        break;
    }

    case DOWN:
    {
        values[loc] = increment(values[loc], -1, maxval[loc]);
        m_lcd.setCursor(1,0);
        m_lcd.write("%u/%02u/%02u %02u:%02u:%02u",
            values[0] + 2000, values[1], values[2],
            values[3], values[4], values[5]);

        m_lcd.setCursor(1, offset[loc]);
        m_lcd.blink_on();
        ret = HANDLED;
        break;
    }

    case UP:
    {
        values[loc] = increment(values[loc], 1, maxval[loc]);
        m_lcd.setCursor(1,0);
        m_lcd.write("%u/%02u/%02u %02u:%02u:%02u",
            values[0] + 2000, values[1], values[2],
            values[3], values[4], values[5]);

        m_lcd.setCursor(1, offset[loc]);
        m_lcd.blink_on();
        ret = HANDLED;
        break;
    }

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
    static uint8_t loc       =  0;
           uint8_t offset[3] = {5,12,19};
           uint8_t maxval    = 99;
    event_ret ret = ERROR;

    static union
    {
        uint8_t         bytes[3];
        Settings::Lcd   values;
    } buffer;

    switch (newEvent)
    {
        case FOCUS:
        {
            Settings settings;
            buffer.values = settings.getLcd();

            loc = 0;
            m_lcd.clear();
            m_lcd.write("LCD Intensity");

            showrgb(m_lcd, offset[loc], buffer.bytes);
            m_lcd.blink_on();
            ret = HANDLED;
            break;
        }
        case TICK:
            ret = HANDLED;
            break;

        case CLICK:
            // go to next loc/item until all items are entered
            if (++loc < 3)
                m_lcd.setCursor(1, offset[loc]);
            else
            {
                Settings settings;
                settings.setLcd(buffer.values);
                m_lcd.blink_off();
                m_currentMenu = &Menu::setLcd;
            }
            ret = HANDLED;
            break;

        case DOWN:
            buffer.bytes[loc] = increment(buffer.bytes[loc],-1, maxval);
            showrgb(m_lcd, offset[loc], buffer.bytes);
            ret = HANDLED;
            break;

        case UP:
            buffer.bytes[loc] = increment(buffer.bytes[loc], 1, maxval);
            showrgb(m_lcd, offset[loc], buffer.bytes);
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
