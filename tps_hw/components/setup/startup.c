
#include "freertos/FreeRTOS.h"
#include "startup.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "logic.h"
#include "esp_log.h"
#include "tps_lcd.h"

#include "tps_mqtt.h"
#include "tps_wifi.h"

const char *TOPIC_ESP = "/tps/pickingface/002/esp";
const char *TOPIC_SYS = "/tps/pickingface/002/sys";

void initSetup()
{
    ESP_LOGI("The Picking Solution", "INICIANDO");
    initHAL();
    lcd_init();

    set_LED_VERDE(FALSE);
    set_LED_VERMELHO(FALSE);
    //initWifi();
    //initMqtt(TOPIC_ESP, TOPIC_SYS);

    // xTaskCreate(
    //     confirma,  /* Function that implements the task. */
    //     "T1",      /* Text name for the task. */
    //     1000,      /* Stack size in words, not bytes. */
    //     (void *)1, /* Parameter passed into the task. */
    //     1,         /* Priority at which the task is created. */
    //     NULL);

    // xTaskCreate(
    //     decremento, /* Function that implements the task. */
    //     "T2",       /* Text name for the task. */
    //     1000,       /* Stack size in words, not bytes. */
    //     (void *)1,  /* Parameter passed into the task. */
    //     1,          /* Priority at which the task is created. */
    //     NULL);

    // xTaskCreate(
    //     incremento, /* Function that implements the task. */
    //     "T3",       /* Text name for the task. */
    //     1000,       /* Stack size in words, not bytes. */
    //     (void *)1,  /* Parameter passed into the task. */
    //     1,          /* Priority at which the task is created. */
    //     NULL);
}