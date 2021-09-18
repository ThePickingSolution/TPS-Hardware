#ifndef __HAL__
#define __HAL__

#include "datatypes.h"

void initHAL();

// Altera o sinal do pino de Teste
void set_LED(boolean signal);
void get_pin();
boolean verifica_incremento();
boolean verifica_decremento();
boolean verifica_confirma();

#endif
