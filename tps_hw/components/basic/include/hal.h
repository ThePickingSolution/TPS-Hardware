#ifndef __HAL__
#define __HAL__

#include "datatypes.h"

/* ESP8266 PIN / GPIO FIXO */
#define ESP_GPIO_D0 GPIO_NUM_16
#define ESP_GPIO_D1 GPIO_NUM_5
#define ESP_GPIO_D2 GPIO_NUM_4
#define ESP_GPIO_D3 GPIO_NUM_0
#define ESP_GPIO_D4 GPIO_NUM_2
#define ESP_GPIO_D5 GPIO_NUM_14
#define ESP_GPIO_D6 GPIO_NUM_12
#define ESP_GPIO_D7 GPIO_NUM_13
#define ESP_GPIO_D8 GPIO_NUM_15
#define ESP_GPIO_RX GPIO_NUM_3
#define ESP_GPIO_TX GPIO_NUM_1
#define ESP_GPIO_SD2 GPIO_NUM_9
#define ESP_GPIO_SD3 GPIO_NUM_10

/*
Para mudar a configuração GPIO, alterar os defines HAL_
*/
#define HAL_LCD_RS ESP_GPIO_D0
#define HAL_LCD_EN ESP_GPIO_D1
#define HAL_LCD_D4 ESP_GPIO_D5
#define HAL_LCD_D5 ESP_GPIO_D6
#define HAL_LCD_D6 ESP_GPIO_D7
#define HAL_LCD_D7 ESP_GPIO_D8

#define HAL_LED_RED ESP_GPIO_D4
#define HAL_BTN_CONF ESP_GPIO_D2
#define HAL_BTN_DEC ESP_GPIO_RX
#define HAL_BTN_INC ESP_GPIO_D3

/*
Seleção de Pinos
*/
#define GPIO_INPUT_BTN ((1ULL << HAL_BTN_CONF) | (1ULL << HAL_BTN_DEC) | (1ULL << HAL_BTN_INC))
#define GPIO_OUTPUT_LEDS (1ULL << HAL_LED_RED)
#define GPIO_OUTPUT_LCD ((1ULL << HAL_LCD_RS) | (1ULL << HAL_LCD_EN) | (1ULL << HAL_LCD_D4) | (1ULL << HAL_LCD_D5) | (1ULL << HAL_LCD_D6) | (1ULL << HAL_LCD_D7))

#define GPIO_INPUT_SEL GPIO_INPUT_BTN
#define GPIO_OUTPUT_SEL (GPIO_OUTPUT_LEDS | GPIO_OUTPUT_LCD)

void initHAL();
void set_LED_VERMELHO(boolean signal);

boolean verifica_incremento();
boolean verifica_decremento();
boolean verifica_confirma();

#endif
