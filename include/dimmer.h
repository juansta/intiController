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

class Dimmer
{
public:
    Dimmer();
    ~Dimmer();

    void setLcd(uint16_t r, uint16_t g, uint16_t b);

    void setWhite(uint8_t w);
    void setRoyalBlue(uint8_t rb);
    void setBlue(uint8_t b);
    void setGreen(uint8_t w);
    void setRed(uint8_t w);
    void setYellow(uint8_t w);

private:
    static const uint8_t PCA9685         = 0x80;
    static const uint8_t READ            = 0x01;
    static const uint8_t WRITE           = 0x00;

    static const uint8_t PCA9685_SUBADR1 = 0x02;
    static const uint8_t PCA9685_SUBADR2 = 0x03;
    static const uint8_t PCA9685_SUBADR3 = 0x04;

    static const uint8_t MODE1           = 0x00;
    static const uint8_t MODE2           = 0x01;

    static const uint8_t MODE1_RESTART    = (1 << 7);
    static const uint8_t MODE1_EXTCLK     = (1 << 6);
    static const uint8_t MODE1_AUTOINC    = (1 << 5);
    static const uint8_t MODE1_SLEEP      = (1 << 4);
    static const uint8_t MODE1_RESP_SUB1  = (1 << 3);
    static const uint8_t MODE1_RESP_SUB2  = (1 << 2);
    static const uint8_t MODE1_RESP_SUB3  = (1 << 1);
    static const uint8_t MODE1_RESP_ACALL = (1 << 0);

    static const uint8_t MODE2_INVERT     = (1 << 4);
    static const uint8_t MODE2_OCH        = (1 << 3);
    static const uint8_t MODE2_OUTDRV     = (1 << 2);
    static const uint8_t MODE2_LEDn0      = (0);
    static const uint8_t MODE2_LEDn1      = (1);
    static const uint8_t MODE2_LEDnHighZ  = (2);

    static const uint8_t PCA9685_PRESCALE = 0x1E;

    static const uint8_t LED0_ON_L  = 0x06;
    static const uint8_t LED0_ON_H  = 0x07;
    static const uint8_t LED0_OFF_L = 0x08;
    static const uint8_t LED0_OFF_H = 0x09;

    static const uint8_t LED1_ON_L  = 0x0A;
    static const uint8_t LED1_ON_H  = 0x0B;
    static const uint8_t LED1_OFF_L = 0x0C;
    static const uint8_t LED1_OFF_H = 0x0D;

    static const uint8_t LED2_ON_L  = 0x0E;
    static const uint8_t LED2_ON_H  = 0x0F;
    static const uint8_t LED2_OFF_L = 0x10;
    static const uint8_t LED2_OFF_H = 0x11;

    static const uint8_t LED3_ON_L  = 0x12;
    static const uint8_t LED3_ON_H  = 0x13;
    static const uint8_t LED3_OFF_L = 0x14;
    static const uint8_t LED3_OFF_H = 0x15;

    static const uint8_t LED4_ON_L  = 0x16;
    static const uint8_t LED4_ON_H  = 0x17;
    static const uint8_t LED4_OFF_L = 0x18;
    static const uint8_t LED4_OFF_H = 0x19;

    static const uint8_t LED5_ON_L  = 0x1A;
    static const uint8_t LED5_ON_H  = 0x1B;
    static const uint8_t LED5_OFF_L = 0x1C;
    static const uint8_t LED5_OFF_H = 0x1D;

    static const uint8_t LED6_ON_L  = 0x1E;
    static const uint8_t LED6_ON_H  = 0x1F;
    static const uint8_t LED6_OFF_L = 0x20;
    static const uint8_t LED6_OFF_H = 0x21;

    static const uint8_t LED7_ON_L  = 0x22;
    static const uint8_t LED7_ON_H  = 0x23;
    static const uint8_t LED7_OFF_L = 0x24;
    static const uint8_t LED7_OFF_H = 0x25;

    static const uint8_t LED8_ON_L  = 0x26;
    static const uint8_t LED8_ON_H  = 0x27;
    static const uint8_t LED8_OFF_L = 0x28;
    static const uint8_t LED8_OFF_H = 0x29;

    static const uint8_t LED9_ON_L  = 0x2A;
    static const uint8_t LED9_ON_H  = 0x2B;
    static const uint8_t LED9_OFF_L = 0x2C;
    static const uint8_t LED9_OFF_H = 0x2D;

    static const uint8_t LED10_ON_L  = 0x2E;
    static const uint8_t LED10_ON_H  = 0x2F;
    static const uint8_t LED10_OFF_L = 0x30;
    static const uint8_t LED10_OFF_H = 0x31;

    static const uint8_t LED11_ON_L  = 0x32;
    static const uint8_t LED11_ON_H  = 0x33;
    static const uint8_t LED11_OFF_L = 0x34;
    static const uint8_t LED11_OFF_H = 0x35;

    static const uint8_t LED12_ON_L  = 0x36;
    static const uint8_t LED12_ON_H  = 0x37;
    static const uint8_t LED12_OFF_L = 0x38;
    static const uint8_t LED12_OFF_H = 0x39;

    static const uint8_t LED13_ON_L  = 0x3A;
    static const uint8_t LED13_ON_H  = 0x3B;
    static const uint8_t LED13_OFF_L = 0x3C;
    static const uint8_t LED13_OFF_H = 0x3D;

    static const uint8_t LED14_ON_L  = 0x3E;
    static const uint8_t LED14_ON_H  = 0x3F;
    static const uint8_t LED14_OFF_L = 0x40;
    static const uint8_t LED14_OFF_H = 0x41;

    static const uint8_t LED15_ON_L  = 0x42;
    static const uint8_t LED15_ON_H  = 0x43;
    static const uint8_t LED15_OFF_L = 0x44;
    static const uint8_t LED15_OFF_H = 0x45;

    static const uint8_t ALLLED_ON_L  = 0xFA;
    static const uint8_t ALLLED_ON_H  = 0xFB;
    static const uint8_t ALLLED_OFF_L = 0xFC;
    static const uint8_t ALLLED_OFF_H = 0xFD;

    void setFrequency(float freq);



    void    write(uint8_t addr, uint8_t d);
    uint8_t read (uint8_t addr);
};
