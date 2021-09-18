#ifndef TPS_WIFI_H
#define TPS_WIFI_H

#include <string.h>
#include "freertos/FreeRTOS.h"

#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "nvs.h"
#include "nvs_flash.h"


/* The examples use WiFi configuration that you can set via project configuration menu
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/

// #define EXAMPLE_ESP_WIFI_SSID      "copel-65"
// #define EXAMPLE_ESP_WIFI_PASS      "72076500"

#define EXAMPLE_ESP_WIFI_SSID      "FE94_Oi_Fibra"
#define EXAMPLE_ESP_WIFI_PASS      "9mEUY3p9"

#define EXAMPLE_ESP_MAXIMUM_RETRY  10


/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1


void initWifi();

#endif // PCHRONO_H