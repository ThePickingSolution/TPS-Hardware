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

void setup_led_pin(){
	gpio_config_t io_conf;

	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = 0x0000000000000001;
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);
}

void initHAL(){
	setup_led_pin();
}

void set_LED(boolean signal){
	printf(signal ? "HIGH ":"LOW ");
	fflush(stdout);
	
	esp_err_t err = gpio_set_level(GPIO_NUM_0,signal ? 1:0);
	printf("%d\n",err);
}




// Retorna se o botão de confirmação está precionado
boolean getConfirm(){
	return FALSE;
}
// Retorna se o botão de incremento está precionado
boolean getIncrement(){
	return FALSE;
}
// Retorna se o botão de decremento está precionado
boolean getDecrement(){
	return FALSE;
}

// Escreve a mensagem para o usuario
void writeMessage(char* message, int8 line){
	//printf(message);
}
