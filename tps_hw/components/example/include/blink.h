#ifndef BLINK_H
#define BLINK_H

#include "FreeRTOS.h"
#include "datatypes.h"

void blink_setup();

void blink_task(void* params);
void incremento(void* params);
void decremento(void* params);
void confirma(void* params);

#endif // BLINK_H
