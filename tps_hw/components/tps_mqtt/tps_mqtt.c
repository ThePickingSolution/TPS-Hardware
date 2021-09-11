

#include "tps_mqtt.h"

char* TPS_MQTT_TOPIC_ESP;
char* TPS_MQTT_TOPIC_SYS;

esp_mqtt_client_handle_t client_handle;



esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    const char *TAG = "TPS";
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");

            msg_id = esp_mqtt_client_subscribe(client, TPS_MQTT_TOPIC_SYS, 2);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            esp_mqtt_client_start(client_handle);
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:

            chegouMensagem(event->data);

            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    const char *TAG = "TPS";
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    mqtt_event_handler_cb(event_data);
}


void initMqtt(char* topic_esp, char* topic_sys){
    TPS_MQTT_TOPIC_ESP = topic_esp;
    TPS_MQTT_TOPIC_SYS = topic_sys;
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = "mqtt://mqtt.eclipseprojects.io",
        .port = 1883,
        //.transport = MQTT_TRANSPORT_OVER_TCP,
    };
    
    client_handle = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client_handle, ESP_EVENT_ANY_ID, mqtt_event_handler, client_handle);
    
    esp_mqtt_client_start(client_handle);
}

void envia_mensagem(char* mensagem){
    const char *TAG = "TPS";
    int msg_id = esp_mqtt_client_publish(client_handle, TPS_MQTT_TOPIC_ESP, mensagem, strlen(mensagem), 2, 0);
    ESP_LOGI(TAG, "Mensagem enviada, msg_id=%d", msg_id);
}
