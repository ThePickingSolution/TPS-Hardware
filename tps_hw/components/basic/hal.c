/*
Camada de Abstracao do Hardware (HAL) para execucao no Visual Studio
*/

#include <stdio.h>
//#include <conio.h>

#include "FreeRTOS.h"

#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "queue.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0    16
#define GPIO_OUTPUT_IO_1    13
#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<GPIO_OUTPUT_IO_0) | (1ULL<<GPIO_OUTPUT_IO_1))
#define GPIO_INPUT_IO_0     5
#define GPIO_INPUT_IO_1     4
#define GPIO_INPUT_IO_2     14
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1) | (1ULL<<GPIO_INPUT_IO_2))
//#define GPIO_INPUT_PIN_SEL  1ULL<<GPIO_INPUT_IO_0

//int qtd = 0;

void setup_led_pin(){
	gpio_config_t io_confOUT;
	gpio_config_t io_confIN;
	io_confOUT.mode = GPIO_MODE_OUTPUT;
	io_confOUT.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_confOUT.pull_down_en = 0;
	io_confOUT.pull_up_en = 0;
	gpio_config(&io_confOUT);
	io_confIN.pin_bit_mask = GPIO_INPUT_PIN_SEL;
	io_confIN.mode = GPIO_MODE_INPUT;
	io_confIN.pull_down_en = 0;
	io_confIN.pull_up_en = 0;
    gpio_config(&io_confIN);
	//io_conf.mode = GPIO_MODE_INPUT;
	//io_conf.pin_bit_mask = 0x0000000000000001;
	//io_conf.pull_down_en = 0;
	//io_conf.pull_up_en = 0;
	//gpio_config(&io_conf);
}

void initHAL(){
	setup_led_pin();
}

void set_LED_VERDE(boolean signal){
	//printf(signal ? "HIGH ":"LOW ");
	fflush(stdout);
	esp_err_t err = gpio_set_level(GPIO_OUTPUT_IO_0,signal ? 1:0);
}

void set_LED_VERMELHO(boolean signal){
	//printf(signal ? "HIGH ":"LOW ");
	fflush(stdout);
	esp_err_t err = gpio_set_level(GPIO_OUTPUT_IO_1,signal ? 1:0);
}

void get_pin(){
	// if(gpio_get_level(GPIO_INPUT_IO_0) == 1){
	// 	printf("Apertado\n");
	// 	set_LED(TRUE);
	// }
	// else{
	// 	printf("N Apertado\n");
	// 	set_LED(FALSE);
	// }
	// fflush(stdout);
}


const TickType_t hal_delay_50ms = 50 / portTICK_PERIOD_MS;

boolean verifica_incremento(){
	boolean high = FALSE;
	if(gpio_get_level(GPIO_INPUT_IO_1) == 1){
		high = TRUE;
		while(gpio_get_level(GPIO_INPUT_IO_1) == 1){ vTaskDelay(hal_delay_50ms);}
	}
	return high;
}

boolean verifica_decremento(){
	boolean high = FALSE;
	if(gpio_get_level(GPIO_INPUT_IO_2) == 1){
		high = TRUE;
		while(gpio_get_level(GPIO_INPUT_IO_2) == 1){ vTaskDelay(hal_delay_50ms);}
	}
	return high;
}

boolean verifica_confirma(){
	boolean high = FALSE;
	if(gpio_get_level(GPIO_INPUT_IO_0) == 1){
		high = TRUE;
		while(gpio_get_level(GPIO_INPUT_IO_0) == 1) { vTaskDelay(hal_delay_50ms);}
	}
	return high;
}

