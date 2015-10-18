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

#include <avr/io.h>
#include <math.h>
#include <led.h>
#include <settings.h>

Led::Led()
    : m_white (WHITE),
      m_rblue (ROYAL_BLUE),
      m_blue  (BLUE),
      m_red   (RED),
      m_green (GREEN),
      m_violet(VIOLET),
      m_yellow(YELLOW)
{
    m_dimmers[WHITE].dimmer      = &m_white;
    m_dimmers[ROYAL_BLUE].dimmer = &m_rblue;
    m_dimmers[BLUE].dimmer       = &m_blue;
    m_dimmers[RED].dimmer        = &m_red;
    m_dimmers[GREEN].dimmer      = &m_green;
    m_dimmers[VIOLET].dimmer     = &m_violet;
    m_dimmers[YELLOW].dimmer     = &m_yellow;

    // configure shutdown pin
    DDRC   |= (1 << PC7);

    disable();
}

void Led::disable()
{
    // set shutdown signal high
    PORTC  |= (1 << PC7);
}

void Led::enable()
{
    // set shutdown signal low
    PORTC  &= ~(1 << PC7);
}

void Led::setMode(eChannel channel, eMode mode, uint16_t delay)
{
    m_dimmers[channel].mode = mode;
    m_dimmers[channel].delay = delay;
}

void Led::tick()
{
    Channel   * dimmer = m_dimmers;

    for (uint8_t channel = 0; channel < 7; channel++, dimmer++)
    {

    }
}
