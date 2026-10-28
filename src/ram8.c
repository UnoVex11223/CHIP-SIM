#include "ram8.h"

uint16_t call_ram8(RAM8 *ram,  uint16_t in, uint8_t address, bool load)
{
    if (address >= RAM8_SIZE)
    {
        return 0;
    }

    if (load)
    {
        ram -> registers[address] = in;
    }

    return ram -> registers[address];
}

