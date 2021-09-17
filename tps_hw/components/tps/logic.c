
#include "FreeRTOS.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "portmacro.h"
#include "tps_mqtt.h"



void incremento(void* params){
    printf("TASK INCREMENTO\n");
    // envia_mensagem("CONFIRMA MOCKADO");
    for(;;){
        if(verifica_incremento())
            envia_mensagem("INCREMENTO");
    }
}

void decremento(void* params){
    printf("TASK DECREMENTO\n");
    // envia_mensagem("CONFIRMA MOCKADO");
    for(;;){
        if(verifica_decremento())
            envia_mensagem("DECREMENTO");
    }
}

void confirma(void* params){
    printf("TASK CONFIRMA\n");
    // envia_mensagem("CONFIRMA MOCKADO");
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