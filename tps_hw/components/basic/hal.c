/*
Camada de Abstracao do Hardware (HAL) para execucao no Visual Studio
*/

#include <stdio.h>

#include "FreeRTOS.h"

#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "queue.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0 16
#define GPIO_OUTPUT_IO_1 13
#define GPIO_OUTPUT_PIN_SEL ((1ULL << GPIO_OUTPUT_IO_0) | (1ULL << GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_IO_0 5
#define GPIO_INPUT_IO_1 4
#define GPIO_INPUT_IO_2 14
#define GPIO_INPUT_PIN_SEL ((1ULL << GPIO_INPUT_IO_0) | (1ULL << GPIO_INPUT_IO_1) | (1ULL << GPIO_INPUT_IO_2))

const TickType_t hal_delay_50ms = 50 / portTICK_PERIOD_MS;

void setup_btns_pins()
{
	gpio_config_t io_confIN;
	io_confIN.pin_bit_mask = GPIO_INPUT_PIN_SEL;
	io_confIN.mode = GPIO_MODE_INPUT;
	io_confIN.pull_down_en = 0;
	io_confIN.pull_up_en = 0;
	gpio_config(&io_confIN);
}

void setup_leds_pins()
{
	gpio_config_t io_confOUT;
	io_confOUT.mode = GPIO_MODE_OUTPUT;
	io_confOUT.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_confOUT.pull_down_en = 0;
	io_confOUT.pull_up_en = 0;
	gpio_config(&io_confOUT);
}

void initHAL()
{
	setup_btns_pins();
	setup_leds_pins();
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
