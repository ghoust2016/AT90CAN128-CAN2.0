/*
*/

#include "config.h"

void GPIOD_init(void)
{
    GPIOD_PIN5_OUTPUT;
    GPIOD_PIN6_INPUT;

    GPIOD_PIN5_PULL_UP;
    GPIOD_PIN6_PULL_UP;
}
