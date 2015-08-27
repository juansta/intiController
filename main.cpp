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
 *
 * intiLED is a hardware and softwasre platform used to control high
 * power LED strings.
 *
 */

#include <rotary.h>
#include <rtc.h>
#include <menu.h>
#include <settings.h>

#include <avr/power.h>
#include <avr/interrupt.h>

int main(void)
{
    Rotary rotary;
    Rtc    rtc;
    Menu   menu;
    Settings settings;
    Timer   timer;

    clock_prescale_set(clock_div_1);

    sei();

    while (1)
    {
        // check for one second tick
        // this is used for user type interactions and
        // is derived from the real time clock IRQ pulse
        if (rtc.tick())
            menu.process(Menu::TICK);

        // check for our internal timer tick
        // this is configured to be triggered
        if (timer.tick())
            menu.process(Menu::FAST_TICK);

        // check our rotary controller for any events
        Rotary::button btn = rotary.check();
        if (btn == Rotary::CLICK)
        {
            menu.process(Menu::CLICK);
        }
        else if (btn == Rotary::LEFT)
        {
            menu.process(Menu::DOWN);
        }
        else if (btn == Rotary::RIGHT)
        {
            menu.process(Menu::UP);
        }
    }

    cli();

    return 0;
}
