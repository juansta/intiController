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

class Rotary
{
public:
    /**
     * @brief The button enum defines possible rotary encoder states
     */
    enum button {NOTHING = 0, CLICK, RIGHT, LEFT};

    Rotary();

    /**
     * @brief Check for any events that have been registered by the interrupt service routine
     * @return button state
     */
    button check();

private:
};
