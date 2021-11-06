#include <stdio.h>

#include "FreeRTOS.h"

#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "queue.h"
#include "esp_log.h"
#include "driver/gpio.h"

/*DEFINES ESTAO NO hal.h*/

/* HAL consts */
const TickType_t hal_delay_50ms = 50 / portTICK_PERIOD_MS;
const TickType_t hal_delay_20ms = 20 / portTICK_PERIOD_MS;

/* HAL functions */
void setup_pins_input();
void setup_pins_output();

void initHAL()
{
	ESP_LOGI("The Picking Solution - HAL", "INIT");
	setup_pins_input();
	setup_pins_output();
}
void setup_pins_input()
{
	gpio_config_t io_confIN;
	io_confIN.mode = GPIO_MODE_INPUT;
	io_confIN.pin_bit_mask = GPIO_INPUT_SEL;
	io_confIN.pull_down_en = 0;
	io_confIN.pull_up_en = 0;
	io_confIN.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&io_confIN);
	ESP_LOGI("The Picking Solution - HAL", "Setup input OK");
}
void setup_pins_output()
{
	gpio_config_t io_confOUT;
	io_confOUT.mode = GPIO_MODE_OUTPUT;
	io_confOUT.pin_bit_mask = GPIO_OUTPUT_SEL;
	io_confOUT.pull_down_en = 0;
	io_confOUT.pull_up_en = 0;
	gpio_config(&io_confOUT);
	ESP_LOGI("The Picking Solution - HAL", "Setup output OK");
}

void set_LED_VERMELHO(boolean signal)
{
	esp_err_t err = gpio_set_level(HAL_LED_RED, signal ? 1 : 0);
	ESP_LOGI("The Picking Solution - HAL", signal ? "LED vermelho ON" : "LED vermelho OFF");
}

boolean verifica_incremento()
{
	boolean high = FALSE;
	if (gpio_get_level(HAL_BTN_INC) == 1)
	{
		high = TRUE;
		while (gpio_get_level(HAL_BTN_INC) == 1)
		{
			vTaskDelay(hal_delay_50ms);
		}
		ESP_LOGI("The Picking Solution - HAL", "INCREMENTO PRESSIONADO");
	}
	return high;
}

boolean verifica_decremento()
{
	boolean high = FALSE;
	if (gpio_get_level(HAL_BTN_DEC) == 1)
	{
		high = TRUE;
		while (gpio_get_level(HAL_BTN_DEC) == 1)
		{
			vTaskDelay(hal_delay_50ms);
		}
		ESP_LOGI("The Picking Solution - HAL", "DECREMENTO PRESSIONADO");
	}
	return high;
}

boolean verifica_confirma()
{
	boolean high = FALSE;
	if (gpio_get_level(HAL_BTN_CONF) == 1)
	{
		high = TRUE;
		while (gpio_get_level(HAL_BTN_CONF) == 1)
		{
			vTaskDelay(hal_delay_50ms);
		}
		ESP_LOGI("The Picking Solution - HAL", "CONFIRMA PRESSIONADO");
	}
	return high;
}
