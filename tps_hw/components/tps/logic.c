
#include "FreeRTOS.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "portmacro.h"
#include "tps_mqtt.h"
#include "util_string.h"

int logic_valor = 0;
int max = 0;
char* logic_id = NULL;
const TickType_t logic_task_delay_100ms = 100 / portTICK_PERIOD_MS;

void incremento(void* params){
    printf("TASK INCREMENTO\n");
    const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
    for(;;){
        if(verifica_incremento())
        {
            //envia_mensagem("INCREMENTO");
            logic_valor=logic_valor+1;
                if (logic_valor > max)
            logic_valor = max;
            printf("Quantidade = %d\n", logic_valor);
        }
        vTaskDelay( logic_task_delay_100ms );
    }
}

void decremento(void* params){
    printf("TASK DECREMENTO\n");
    const TickType_t xDelay = 100 / portTICK_PERIOD_MS;
    for(;;){
        if(verifica_decremento())
        {
            //envia_mensagem("DECREMENTO");
            logic_valor=logic_valor-1;
            if (logic_valor < 0)
                logic_valor = 0;
            printf("Quantidade = %d\n", logic_valor);
        }
        vTaskDelay( logic_task_delay_100ms );
    }
}

void confirma(void* params){
    printf("TASK CONFIRMA\n");
    char* msg_envia_default = calloc(50, sizeof(char));
    for(;;){
        if(verifica_confirma())
        {
            char* msg = "CONFIRM;";
            char msg_envia[50];
            char quantidade[3]; 
            itoa(logic_valor, quantidade, 10);
            strcpy(msg_envia,msg_envia_default);
            strcat(msg_envia,msg);
            strcat(msg_envia,logic_id);
            strcat(msg_envia,";0;");
            strcat(msg_envia,quantidade);
            envia_mensagem(msg_envia);
            set_LED_VERDE(FALSE);
            set_LED_VERMELHO(FALSE);
        }
        vTaskDelay( logic_task_delay_100ms );
    }
}

void chegouMensagem(char* mensagem){
    char* msg = str_part(mensagem,'.',0);
    printf("\nMensagem recebida:\n");
    printf(msg);
    char* command = str_part(msg,';',0);
    if(logic_id != NULL)
        str_part_free(logic_id);
    logic_id = str_part(msg,';',1);
    char* qtd = str_part(msg,';',6);
    char* LED_VERDE = str_part(msg,';',3);
    char* LED_VERMELHO = str_part(msg,';',4);
    printf("\nComando:\n");
    printf(command);
	printf("\nId:\n");
    printf(logic_id);
    logic_valor = atoi(qtd);
    max = logic_valor;
	printf("\nQuantidade:\n");
    printf("%d\n", logic_valor);
    int verde = atoi(LED_VERDE);
    int vermelho = atoi(LED_VERMELHO);
    printf("Verde:\n");
    printf("%d\n", verde);
    printf("Vermelho:\n");
    printf("%d\n", vermelho);
    if (verde == 1)
        set_LED_VERDE(TRUE);
    else
        set_LED_VERDE(FALSE);

    if (vermelho == 1)
        set_LED_VERMELHO(TRUE);
    else
        set_LED_VERMELHO(FALSE);
    //Libera memoria alocada !importante!
	str_part_free(msg);
	str_part_free(command);
    str_part_free(qtd);
    str_part_free(LED_VERMELHO);
    str_part_free(LED_VERDE);
}

