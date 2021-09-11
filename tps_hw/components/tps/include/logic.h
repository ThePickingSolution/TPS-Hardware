#ifndef TPS_LOGIC_H
#define TPS_LOGIC_H

#include "FreeRTOS.h"
#include "datatypes.h"
#include "esp_log.h"

void incremento(void* params);
void decremento(void* params);
void confirma(void* params);

void chegouMensagem(const char* mensagem);

#endif // TPS_LOGIC_H
