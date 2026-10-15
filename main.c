#include <stdio.h>
#include <threads.h>
#include "pc.h"
#include "ram8.h"

typedef enum {TICK, TOCK} ClockPhase;

static const struct timespec HALF_CYCLE = {.tv_sec = 1}; 

void print_tick_or_tock(uint16_t current_value, ClockPhase phase)
{
   printf("%s| Value in counter: %u\n", phase == TICK ? "Tick" : "Tock", current_value);
}

int main(void)
{
    RAM8 ram = {};
    
    uint16_t current_value = 0;
    print_tick_or_tock(current_value, TICK);
    thrd_sleep(&HALF_CYCLE, NULL);
    print_tick_or_tock(current_value = call_pc(current_value, 16, 0, 1, 0), TOCK);
    thrd_sleep(&HALF_CYCLE, NULL);
    return 0;
}

