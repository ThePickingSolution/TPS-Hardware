
#include "FreeRTOS.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "portmacro.h"
#include "tps_mqtt.h"
#include "util_string.h"


const TickType_t logic_task_delay_100ms = 100 / portTICK_PERIOD_MS;

void incremento(void* params){
    printf("TASK INCREMENTO\n");
    const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
    // envia_mensagem("CONFIRMA MOCKADO");
    for(;;){
        if(verifica_incremento())
            envia_mensagem("INCREMENTO");
        
        vTaskDelay( logic_task_delay_100ms );
    }
}

void decremento(void* params){
    printf("TASK DECREMENTO\n");
    // envia_mensagem("CONFIRMA MOCKADO");
    const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
    for(;;){
        if(verifica_decremento())
            envia_mensagem("DECREMENTO");
        vTaskDelay( logic_task_delay_100ms );
    }
}

void confirma(void* params){
    printf("TASK CONFIRMA\n");
    // envia_mensagem("CONFIRMA MOCKADO");
    for(;;){
        if(verifica_confirma())
            envia_mensagem("CONFIRMA");
        vTaskDelay( logic_task_delay_100ms );
    }
}

void chegouMensagem(char* mensagem){

    char* msg = str_part(mensagem,'.',0);
    printf("\nMensagem recebida:\n");
    printf(msg);

    char* command = str_part(msg,';',0);
    char* id = str_part(msg,';',1);

    printf("\nComando:\n");
    printf(command);
	printf("\nId:\n");
    printf(id);
	printf("\n");
	
    //Libera memoria alocada !importante!
	str_part_free(msg);
	str_part_free(command);
	str_part_free(id);

}

