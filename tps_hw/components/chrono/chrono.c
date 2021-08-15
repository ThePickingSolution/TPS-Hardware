
#include "FreeRTOS.h"
#include "datatypes.h"
#include "chrono.h"
#include "task.h"
#include "timers.h"

//Com Bug -> Provavelmente os ticks esão estourando o tamanho da memoria. Descobrir outra forma de contar o tempo

TickType_t msPerTick = portTICK_PERIOD_MS;

pChrono pChronoCreate(uint32 ms){
    pChrono c;
    c.time = (TickType_t)(ms);
    return c;
}
void pChronoStart(pChrono* chrono){
    TickType_t ticks = xTaskGetTickCount();
    TickType_t ston = (uint32)(ticks * msPerTick);
    chrono->startms = ston;
}
boolean pChronoTimeOver(pChrono* chrono){
    TickType_t ticks = xTaskGetTickCount();
    TickType_t now = (ticks * msPerTick);

    return (chrono->startms + chrono->time) < now;
}