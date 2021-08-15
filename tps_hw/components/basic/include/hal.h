#ifndef __HAL__
#define __HAL__

#include "datatypes.h"

void initHAL();

// Retorna se o botão de confirmação está precionado
boolean getConfirm();
// Retorna se o botão de incremento está precionado
boolean getIncrement();
// Retorna se o botão de decremento está precionado
boolean getDecrement();

// Escreve a mensagem para o usuario
void writeMessage(char* message, int8 line);


// Altera o sinal do pino de Teste
void set_LED(boolean signal);

#endif
