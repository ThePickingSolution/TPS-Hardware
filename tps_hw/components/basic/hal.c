/*
Camada de Abstracao do Hardware (HAL) para execucao no Visual Studio
*/

#include <stdio.h>

#include "FreeRTOS.h"

#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "queue.h"
#include "esp_log.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0 16 //D0
#define GPIO_OUTPUT_IO_1 13 //D7
#define GPIO_INPUT_IO_0 5	
#define GPIO_INPUT_IO_1 4	//D2
#define GPIO_INPUT_IO_2 14	//D5

// #define GPIO_LCD_EN 10 
// #define GPIO_LCD_RS 12 //D6
// #define GPIO_LCD_D4 15 //D8
// #define GPIO_LCD_D5 3  //RX
// #define GPIO_LCD_D6 1  //TX
// #define GPIO_LCD_D7 9  //SD2

#define GPIO_INPUT_PIN_SEL ((1ULL << GPIO_INPUT_IO_0) | (1ULL << GPIO_INPUT_IO_1) | (1ULL << GPIO_INPUT_IO_2))
//#define GPIO_OUTPUT_PIN_SEL ((1ULL << GPIO_OUTPUT_IO_0) | (1ULL << GPIO_OUTPUT_IO_1) | (1ULL << GPIO_LCD_EN) | (1ULL << GPIO_LCD_RS) | (1ULL << GPIO_LCD_D4) | (1ULL << GPIO_LCD_D5) | (1ULL << GPIO_LCD_D6) | (1ULL << GPIO_LCD_D7))
#define GPIO_OUTPUT_PIN_SEL ((1ULL << GPIO_OUTPUT_IO_0) | (1ULL << GPIO_OUTPUT_IO_1))
const TickType_t hal_delay_50ms = 50 / portTICK_PERIOD_MS;
const TickType_t hal_delay_20ms = 20 / portTICK_PERIOD_MS;

void setup_btns_pins()
{
	gpio_config_t io_confIN;
	io_confIN.mode = GPIO_MODE_INPUT;
	io_confIN.pin_bit_mask = GPIO_INPUT_PIN_SEL;
	//io_confIN.pull_down_en = 0;
	//io_confIN.pull_up_en = 0;
	io_confIN.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&io_confIN);
}

void setup_leds_pins()
{
	gpio_config_t io_confOUT;
	io_confOUT.mode = GPIO_MODE_OUTPUT;
	io_confOUT.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_confOUT.pull_down_en = 0;
	io_confOUT.pull_up_en = 0;
	//io_confOUT.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&io_confOUT);
}

void initHAL()
{
	ESP_LOGI("The Picking Solution", "INIT HAL");
	setup_leds_pins();
	ESP_LOGI("The Picking Solution", "setup_leds_pins() OK");
	setup_btns_pins();
	ESP_LOGI("The Picking Solution", "setup_btns_pins() OK");
}

void set_LED_VERDE(boolean signal)
{
	esp_err_t err = gpio_set_level(GPIO_OUTPUT_IO_0, signal ? 1 : 0);
}

void set_LED_VERMELHO(boolean signal)
{
	esp_err_t err = gpio_set_level(GPIO_OUTPUT_IO_1, signal ? 1 : 0);
}

boolean verifica_incremento()
{
	boolean high = FALSE;
	if (gpio_get_level(GPIO_INPUT_IO_1) == 1)
	{
		high = TRUE;
		while (gpio_get_level(GPIO_INPUT_IO_1) == 1)
		{
			vTaskDelay(hal_delay_50ms);
		}
	}
	return high;
}

boolean verifica_decremento()
{
	boolean high = FALSE;
	if (gpio_get_level(GPIO_INPUT_IO_2) == 1)
	{
		high = TRUE;
		while (gpio_get_level(GPIO_INPUT_IO_2) == 1)
		{
			vTaskDelay(hal_delay_50ms);
		}
	}
	return high;
}

boolean verifica_confirma()
{
	boolean high = FALSE;
	if (gpio_get_level(GPIO_INPUT_IO_0) == 1)
	{
		high = TRUE;
		while (gpio_get_level(GPIO_INPUT_IO_0) == 1)
		{
			vTaskDelay(hal_delay_50ms);
		}
	}
	return high;
}

// void envia_display(boolean rs, boolean data[8])
// {
// 	esp_err_t err;
// 	err = gpio_set_level(GPIO_LCD_RS, rs ? 1 : 0);
// 	err = gpio_set_level(GPIO_LCD_EN, 0);

// 	err = gpio_set_level(GPIO_LCD_D4, data[0]);
// 	err = gpio_set_level(GPIO_LCD_D5, data[1]);
// 	err = gpio_set_level(GPIO_LCD_D6, data[2]);
// 	err = gpio_set_level(GPIO_LCD_D7, data[3]);

// 	err = gpio_set_level(GPIO_LCD_EN, 1);
// 	vTaskDelay(hal_delay_20ms);
// 	err = gpio_set_level(GPIO_LCD_EN, 0);
// 	vTaskDelay(hal_delay_50ms);

// 	err = gpio_set_level(GPIO_LCD_D4, data[4]);
// 	err = gpio_set_level(GPIO_LCD_D5, data[5]);
// 	err = gpio_set_level(GPIO_LCD_D6, data[6]);
// 	err = gpio_set_level(GPIO_LCD_D7, data[7]);

// 	err = gpio_set_level(GPIO_LCD_EN, 1);
// 	vTaskDelay(hal_delay_20ms);
// 	err = gpio_set_level(GPIO_LCD_EN, 0);
// 	vTaskDelay(hal_delay_50ms);
// }