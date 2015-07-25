#pragma once

#include <util/delay.h>

__inline void delay_ms(int ms)
{
    for (int i = 0; i < ms; i++)
    {
        _delay_ms(1);
    }
}
