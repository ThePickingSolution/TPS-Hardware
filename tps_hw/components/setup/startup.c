
#include "freertos/FreeRTOS.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "blink.h"

void initSetup(){
    initHAL();
    blink_setup();
    xTaskCreate(
                    confirma,         /* Function that implements the task. */
                    "T1",               /* Text name for the task. */
                   1000,               /* Stack size in words, not bytes. */
                    ( void * ) 1,       /* Parameter passed into the task. */
                    1,                  /* Priority at which the task is created. */
                    NULL );
    printf("TASK CRIADA\n");
    //xTaskCreate(
    //                decremento,         /* Function that implements the task. */
    //                "T1",               /* Text name for the task. */
    //                1000,               /* Stack size in words, not bytes. */
    //                ( void * ) 1,       /* Parameter passed into the task. */
    //                1,                  /* Priority at which the task is created. */
    //                NULL );
    //xTaskCreate(
    //                confirma,         /* Function that implements the task. */
    //                "T1",               /* Text name for the task. */
    //                1000,               /* Stack size in words, not bytes. */
    //                ( void * ) 1,       /* Parameter passed into the task. */
    //                1,                  /* Priority at which the task is created. */
    //                NULL );
}