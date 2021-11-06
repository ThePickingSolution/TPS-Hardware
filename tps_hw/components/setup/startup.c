
#include "freertos/FreeRTOS.h"
#include "startup.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "logic.h"
#include "esp_log.h"
#include "lcd.h"

#include "tps_mqtt.h"
#include "tps_wifi.h"

void setup_task_confirma();
void setup_task_incremento();
void setup_task_decremento();

void init_lcd();
void teste_led();

const char *TOPIC_ESP = "/tps/pickingface/001/esp";
const char *TOPIC_SYS = "/tps/pickingface/001/sys";

//const TickType_t teste_delay = 1000 / portTICK_PERIOD_MS;

//****************** PARA DAR FLASH********************
// COLOCAR D3 EM GND, DAR FLASH, QUANDO ACABAR COLOCAR D3 EM VCC E APERTAR RST
// DESCONECTAR PINO GPIO3

void initSetup()
{
    ESP_LOGI("The Picking Solution", "INIT HAL");
    initHAL();

    ESP_LOGI("The Picking Solution", "INIT WIFI");
    initWifi();

    ESP_LOGI("The Picking Solution", "INIT MQTT");
    initMqtt(TOPIC_ESP, TOPIC_SYS);

    ESP_LOGI("The Picking Solution", "INIT LCD");
    LCD_init();

    ESP_LOGI("The Picking Solution", "SETUP Tasks");
    setup_task_confirma();
    setup_task_incremento();
    setup_task_decremento();
    ESP_LOGI("The Picking Solution", "SETUP Tasks Feito");

    //envia_mensagem("MQTT OK");
    //teste_led();

    init_lcd();
}

void setup_task_confirma()
{
    xTaskCreate(
        confirma,  /* Function that implements the task. */
        "T1",      /* Text name for the task. */
        1000,      /* Stack size in words, not bytes. */
        (void *)1, /* Parameter passed into the task. */
        1,         /* Priority at which the task is created. */
        NULL);
}

void setup_task_decremento()
{
    xTaskCreate(
        decremento, /* Function that implements the task. */
        "T2",       /* Text name for the task. */
        1000,       /* Stack size in words, not bytes. */
        (void *)1,  /* Parameter passed into the task. */
        1,          /* Priority at which the task is created. */
        NULL);
}

void setup_task_incremento()
{
    xTaskCreate(
        incremento, /* Function that implements the task. */
        "T3",       /* Text name for the task. */
        1000,       /* Stack size in words, not bytes. */
        (void *)1,  /* Parameter passed into the task. */
        1,          /* Priority at which the task is created. */
        NULL);
}

void init_lcd()
{
    lcd_limpa();
    lcd_locate(1, 0);
    lcd_str("TPS             ");
    ESP_LOGI("The Picking Solution - LCD", "LCD INIT");
}

void teste_led()
{
    set_LED_VERMELHO(TRUE);
    ESP_LOGI("The Picking Solution", "TESTE LED");
}