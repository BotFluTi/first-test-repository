#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"

void BOARD_InitHardware(void);

static const int8_t morse_salut[] = {
     1, -1,  1, -1,  1,   /* S */
    -3,
     1, -1,  3,            /* A */
    -3,
     1, -1,  3, -1,  1, -1,  1,  /* L */
    -3,
     1, -1,  1, -1,  3,   /* U */
    -3,
     3,                    /* T */
    -7
};

#define MORSE_LEN (sizeof(morse_salut) / sizeof(morse_salut[0]))

static volatile uint8_t sym_index  = 0;
static volatile int8_t  ticks_left = 0;

void SysTick_Handler(void)
{
    if (ticks_left > 0)
    {
        ticks_left--;
        return;
    }

    int8_t sym = morse_salut[sym_index];

    if (sym > 0)
    {
        LED_RED_ON();
        ticks_left = sym - 1;
    }
    else
    {
        LED_RED_OFF();
        ticks_left = (-sym) - 1;
    }

    sym_index = (sym_index + 1) % MORSE_LEN;
}

int main(void)
{
    /* Board pin init */
    BOARD_InitHardware();

    while (1)
    {
    }
}
