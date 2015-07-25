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
#include <lcd.h>
#include <delays.h>
#include <avr/power.h>

int main(void) {
    Rotary rotary(DDRB, 1);
    Lcd lcd;
    float i = 0;

    clock_prescale_set(clock_div_1);

    while (1)
    {
         lcd.home();
         lcd.write("else - %.1f", i);
         _delay_ms(100);

         i = i + 0.1f;
    }

    return 0;
}
