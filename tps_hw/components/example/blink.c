
#include "FreeRTOS.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "portmacro.h"


boolean up = TRUE;

void blink_setup(){
    set_LED(FALSE);
}

void toggle_led(){
    if(up)
        set_LED(TRUE);
    else
        set_LED(FALSE);

    up = !up;
}

void blink_task(void* params){
    //for(;;){
    //  toggle_led();
    //   vTaskDelay(5000 / portTICK_PERIOD_MS);
    //}
    for(;;){
        get_pin();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

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
    for(;;){
        verifica_confirma();
    }
}