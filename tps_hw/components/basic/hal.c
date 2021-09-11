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
#define GPIO_OUTPUT_PIN_SEL  1ULL<<GPIO_OUTPUT_IO_0
#define GPIO_INPUT_IO_0     5
#define GPIO_INPUT_IO_1     9
#define GPIO_INPUT_IO_2     10
//#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1) | (1ULL<<GPIO_INPUT_IO_2))
#define GPIO_INPUT_PIN_SEL  1ULL<<GPIO_INPUT_IO_0

//int qtd = 0;

void setup_led_pin(){
	gpio_config_t io_conf;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);
	io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
	io_conf.mode = GPIO_MODE_INPUT;
    //io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
	//io_conf.mode = GPIO_MODE_INPUT;
	//io_conf.pin_bit_mask = 0x0000000000000001;
	//io_conf.pull_down_en = 0;
	//io_conf.pull_up_en = 0;
	//gpio_config(&io_conf);
}

void initHAL(){
	setup_led_pin();
}

void set_LED(boolean signal){
	printf(signal ? "HIGH ":"LOW ");
	fflush(stdout);
	
	esp_err_t err = gpio_set_level(GPIO_OUTPUT_IO_0,signal ? 1:0);
	printf("%d\n",err);
}

void get_pin(){
	if(gpio_get_level(GPIO_INPUT_IO_0) == 1){
		printf("Apertado\n");
		set_LED(TRUE);
	}
	else{
		printf("N Apertado\n");
		set_LED(FALSE);
	}
	fflush(stdout);
}

int verifica_incremento(int valor){
	if(gpio_get_level(GPIO_INPUT_IO_0) == 0){
		printf("Aguardando botao\n");
		while(gpio_get_level(GPIO_INPUT_IO_0) == 0){};
		gpio_set_level(GPIO_OUTPUT_IO_0,1);
		while(gpio_get_level(GPIO_INPUT_IO_0) == 1){};
		gpio_set_level(GPIO_OUTPUT_IO_0,0);
		printf("incremento apertado\n");
		valor = valor + 1;
		printf("qtd = %d\n", valor);
		return valor;
	}
	fflush(stdout);
	return valor;
}

void verifica_decremento(){
	if(gpio_get_level(GPIO_INPUT_IO_1) == 0){
		//printf("Aguardando botao\n");
		while(gpio_get_level(GPIO_INPUT_IO_1) == 0){};
		while(gpio_get_level(GPIO_INPUT_IO_1) == 1){};
		printf("decremento apertado\n");
		//qtd = qtd - 1;
		//printf("qtd = %d", qtd);
	}
	fflush(stdout);
}

void verifica_confirma(){
	if(gpio_get_level(GPIO_INPUT_IO_0) == 0){
		printf("Aguardando botao\n");
		while(gpio_get_level(GPIO_INPUT_IO_0) == 0){};
		while(gpio_get_level(GPIO_INPUT_IO_0) == 1){};
		printf("CONFIRMA\n");
		gpio_set_level(GPIO_OUTPUT_IO_0,1);
	}
	fflush(stdout);
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
