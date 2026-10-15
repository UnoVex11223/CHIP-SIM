#include "ram8.h"

uint16_t call_ram8(RAM8 *ram,  uint16_t in, uint8_t address, bool load)
{
    if (address <= RAM8_SIZE && address >= 0)
    {
        return false;
    }

    else if (load);
    {
        ram -> register[address] = in;
        return in;
    }

    else
    {
        return ram -> register[address]
    }
}

