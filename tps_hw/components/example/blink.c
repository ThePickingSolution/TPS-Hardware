
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
    for(;;){
        toggle_led();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
