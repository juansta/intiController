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

#pragma once

#include <inttypes.h>
#include <datetime.h>

class Rtc
{
public:
    Rtc();
    ~Rtc();
    void begin() {}
    static void adjust(const DateTime& dt);
    static DateTime now();
    uint8_t isrunning();

    // Set IRQ output state: 0=disabled, 1=1Hz, 2=512Hz.
    void setIRQ(uint8_t state);

    // Set IRQ output active state to LOW or HIGH.
    void setIRQLevel(uint8_t level);

    // Sets the calibration value to given value in the range -31 - 31, which
    // corresponds to -126ppm - +63ppm; see table 13 in th BQ32000 datasheet.
    void setCalibration(int8_t value);
    void setCharger(int state);

    bool tick();

private:
    uint8_t readRegister(uint8_t address);
    bool writeRegister(uint8_t address, uint8_t value);
    bool writeRegister(uint8_t address, uint8_t * values, uint8_t len);

    static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4);  }
    static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10);  }

};
