#ifndef __HAL__
#define __HAL__

#include "datatypes.h"

void initHAL();

// Altera o sinal do pino de Teste
void set_LED_VERDE(boolean signal);
void set_LED_VERMELHO(boolean signal);
boolean verifica_incremento();
boolean verifica_decremento();
boolean verifica_confirma();

#endif
