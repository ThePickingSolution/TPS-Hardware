#ifndef TPS_MQTT_H
#define TPS_MQTT_H

#include "freertos/FreeRTOS.h"
#include "datatypes.h"
#include <stdio.h>
#include <string.h>
#include "esp_event.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "logic.h"


void initMqtt(char* topic_esp, char* topic_sys);

void envia_mensagem(char* mensagem);

#endif // TPS_MQTT_H