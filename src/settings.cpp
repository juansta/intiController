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

#include <settings.h>

Settings::Settings()
    : m_updated(0), m_loaded(false)
{
    refresh();
}
Settings::~Settings()
{}
bool Settings::commit()
{
    bool ret = m_updated;

    m_updated = 0;

    return ret;
}
void Settings::setMaxTotal(uint8_t value)
{
    m_updated |= TOTAL;
    m_config.maxTotal = value;
}
void Settings::setMaxW(uint8_t value)
{
    m_updated |= WHITE;
    m_config.maxW = value;
}
void Settings::setMaxRB(uint8_t value)
{
    m_updated |= ROYAL_BLUE;
    m_config.maxRB = value;
}
void Settings::setMaxB(uint8_t value)
{
    m_updated |= BLUE;
    m_config.maxB = value;
}
void Settings::setMaxR(uint8_t value)
{
    m_updated |= RED;
    m_config.maxR = value;
}
void Settings::setMaxG(uint8_t value)
{
    m_updated |= GREEN;
    m_config.maxG = value;
}
void Settings::setMaxY(uint8_t value)
{
    m_updated |= YELLOW;
    m_config.maxY = value;
}
void Settings::setMaxV(uint8_t value)
{
    m_updated |= VIOLET;
    m_config.maxV = value;
}
bool Settings::getMaxTotal(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxTotal;

    return m_loaded;
}
bool Settings::getMaxW(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxW;

    return m_loaded;
}
bool Settings::getMaxRB(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxRB;

    return m_loaded;
}
bool Settings::getMaxB(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxB;

    return m_loaded;
}
bool Settings::getMaxR(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxR;

    return m_loaded;
}
bool Settings::getMaxG(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxG;

    return m_loaded;
}
bool Settings::getMaxY(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxY;

    return m_loaded;
}
bool Settings::getMaxV(uint8_t&value)
{
    if (m_loaded)
        value = m_config.maxV;

    return m_loaded;
}
bool Settings::refresh()
{
     bool ret = false;

     return ret;
}
