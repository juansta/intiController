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

void Led::step(eDirection direction)
{
    m_white  .setLevel(585*1);
    m_rblue  .setLevel(585*2);
    m_blue   .setLevel(585*3);
    m_red    .setLevel(585*4);
    m_green  .setLevel(585*5);
    m_violet .setLevel(585*6);
    m_yellow .setLevel(585*7);
}
