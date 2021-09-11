
#include "FreeRTOS.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "portmacro.h"
#include "tps_mqtt.h"



void incremento(void* params){
    int valor = 0;
    for(;;){
        valor = verifica_incremento(valor);
    }
}

void decremento(void* params){
    for(;;){
        verifica_decremento();
    }
}

void confirma(void* params){
    printf("TASK CONFIRMA\n");
    envia_mensagem("CONFIRMA MOCKADO");
    for(;;){
        if(verifica_confirma())
            envia_mensagem("CONFIRMA");
    }
}




void chegouMensagem(const char* mensagem){
    //ESP_LOGI("TPS", "Mensagem recebida: %s", mensagem);
    printf("Mensagem recebida \n");
    printf(mensagem);
}