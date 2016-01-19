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
#include <timer.h>
#include <led.h>
#include <usb.h>

#include <avr/power.h>
#include <avr/interrupt.h>

int main(void)
{
    Usb      usb;
    Rtc      rtc;
    Timer    timer;
    Led      led;

    clock_prescale_set(clock_div_1);

    sei();

    while (1)
    {
        usb.tick();

        // check for one second tick
        // this is used for user type interactions and
        // is derived from the real time clock IRQ pulse
        if (rtc.tick())
            usb.sendData();

        // check for our internal timer tick
        // this is configured to be triggered
        if (timer.ticked())
            usb.getData();
    }

    cli();

    return 0;
}
