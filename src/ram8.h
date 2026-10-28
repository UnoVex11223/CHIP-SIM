#ifndef RAM8_H
#define RAM8_H

#include <stdbool.h>
#include <stdint.h>

enum { RAM8_SIZE = 8};

typedef struct
{
    uint16_t registers[RAM8_SIZE];
} RAM8;

uint16_t call_ram8(RAM8 *ram,  uint16_t in, uint8_t address, bool load);

#endif
