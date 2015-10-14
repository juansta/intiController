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

#include <controller.h>

Controller::Controller()
    : m_mode(AUTO)
{}
void Controller::setMode(eMode mode)
{
    m_mode = mode;
}
void Controller::newTime(const DateTime & currTime)
{
    // check if we've gone past any sunrise/sunset etc
}
void Controller::tick()
{}
void Controller::setWhite (const uint16_t & white)
{}
void Controller::setRBlue (const uint16_t & rblue)
{}
void Controller::setBlue  (const uint16_t & blue)
{}
void Controller::setRed   (const uint16_t & red)
{}
void Controller::setGreen (const uint16_t & green)
{}
void Controller::setViolet(const uint16_t & violet)
{}
void Controller::setAmber (const uint16_t & amber)
{
    if (m_mode == MANUAL)
    {

    }
}
