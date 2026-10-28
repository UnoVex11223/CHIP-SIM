#include "pc.h"

uint16_t call_pc(uint16_t current_value, uint16_t in, int reset, int load, int inc)
{
    if (reset == 1)
    {
        return 0;
    }

    else if (load == 1)
    {
        return in;
    }

    else if (inc == 1)
    {
        return current_value + 1;
    }

    else
        return current_value;
}

