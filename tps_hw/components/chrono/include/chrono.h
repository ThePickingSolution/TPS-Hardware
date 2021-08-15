#ifndef PCHRONO_H
#define PCHRONO_H

#include "datatypes.h"
#include "task.h"

typedef struct{
    TickType_t startms;
    TickType_t time;
}pChrono;

pChrono pChronoCreate(uint32 ms);
void pChronoStart(pChrono* chrono);
boolean pChronoTimeOver(pChrono* chrono);

#endif // PCHRONO_H