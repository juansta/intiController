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

#include <global.h>
#include <rotary.h>
#include <delays.h>
#include <lcd.h>
#include <timer.h>


#include <avr/power.h>
#include <avr/interrupt.h>


int main(void)
{
    Lcd    lcd;
    Timer  timer;
    Rotary rotary;

    int btn_cnt = 0;
    int btn_rot = 0;

    clock_prescale_set(clock_div_1);

    sei();

    while (1)
    {
        lcd.home();
        Rotary::button btn = rotary.check();
        if (btn == Rotary::CLICK)
        {
            lcd.home();
            lcd.write("PC-%u", btn_cnt++);
        }
        else if (btn == Rotary::LEFT)
        {
            lcd.setCursor(1, 0);
            lcd.write("COUNT-%d   ", btn_rot--);
        }
        else if (btn == Rotary::RIGHT)
        {
            lcd.setCursor(1, 0);
            lcd.write("COUNT-%d   ", btn_rot++);
        }

        if (timer.ticked())
        {
            lcd.home();

            timer.reset();
        }
    }

    cli();

    return 0;
}
