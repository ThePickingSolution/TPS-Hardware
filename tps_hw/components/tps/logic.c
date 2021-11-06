
#include "FreeRTOS.h"
#include "datatypes.h"
#include "hal.h"
#include "task.h"
#include "portmacro.h"
#include "tps_mqtt.h"
#include "util_string.h"
#include "esp_heap_caps.h"
#include "lcd.h"

#define LOGIC_SEPARANDO 0
#define LOGIC_CONFIRMANDO 1
#define LOGIC_ESPERANDO 1

boolean checkAndDo_PICK(char *, char *);
boolean checkAndDo_CONFIRM(char *, char *);
boolean checkAndDo_REJECTED(char *, char *);
boolean checkAndDo_DONE(char *, char *);
boolean checkAndDo_APPROVE(char *, char *);
boolean checkAndDo_CANCEL(char *, char *);
boolean checkAndDo_ERROR(char *, char *);
void printLCD(char *, boolean);

int logic_estado = LOGIC_ESPERANDO;
int logic_valor = 0;
int logic_max_qty = 0;
char *logic_id = NULL;

const TickType_t logic_task_delay_100ms = 100 / portTICK_PERIOD_MS;

const TickType_t logic_task_delay_3s = 3000 / portTICK_PERIOD_MS;

void incremento(void *params)
{
    ESP_LOGI("The Picking Solution - INCREMENTO", "TASK INCREMENTO INICIADA");
    for (;;)
    {
        if (verifica_incremento())
        {
            logic_valor = logic_valor + 1;

            if (logic_valor > logic_max_qty)
                logic_valor = logic_max_qty;

            ESP_LOGI("The Picking Solution - INCREMENTO", "Quantidade = %d", logic_valor);

            char quantidade[3];
            itoa(logic_valor, quantidade, 10);
            char *defStr = "                ;";
            char *l1 = str_part(defStr, ';', 0);
            int qtyLen = strlen(quantidade);
            int qtyPos = 16 - qtyLen;
            for (int i = qtyPos; i < 16; i++)
            {
                l1[i] = quantidade[i - 15];
            }

            lcd_limpa();
            printLCD(l1, TRUE);
        }
        vTaskDelay(logic_task_delay_100ms);
    }
}

void decremento(void *params)
{
    ESP_LOGI("The Picking Solution - DECREMENTO", "TASK DECREMENTO INICIADA");
    for (;;)
    {
        if (verifica_decremento())
        {
            logic_valor = logic_valor - 1;

            if (logic_valor < 0)
                logic_valor = 0;

            ESP_LOGI("The Picking Solution - DECREMENTO", "Quantidade = %d", logic_valor);

            char quantidade[3];
            itoa(logic_valor, quantidade, 10);

            char *defStr = "                ;";
            char *l1 = str_part(defStr, ';', 0);
            int qtyLen = strlen(quantidade);
            int qtyPos = 16 - qtyLen;
            for (int i = qtyPos; i < 16; i++)
            {
                l1[i] = quantidade[i - 15];
            }

            lcd_limpa();
            printLCD(l1, TRUE);
        }
        vTaskDelay(logic_task_delay_100ms);
    }
}

void confirma(void *params)
{
    ESP_LOGI("The Picking Solution - INCREMENTO", "TASK CONFIRMA INICIADA");
    for (;;)
    {
        if (verifica_confirma() && logic_estado == LOGIC_SEPARANDO)
        {
            logic_estado = LOGIC_CONFIRMANDO;
            char *msg = "CONFIRM;";
            char *msg_envia = heap_caps_calloc(50, sizeof(char), MALLOC_CAP_8BIT);
            char quantidade[3];
            char *msg_pos = &(msg_envia[0]);

            itoa(logic_valor, quantidade, 10);
            strcat(msg_pos, msg);
            strcat(msg_pos, logic_id);
            strcat(msg_pos, ";");
            strcat(msg_pos, quantidade);
            envia_mensagem(msg_pos);

            lcd_limpa();
            printLCD("CONFIRMANDO...  ", TRUE);

            ESP_LOGI("The Picking Solution - CONFIRMA", "CONFIRMADO");
            str_part_free(msg_envia);
        }
        vTaskDelay(logic_task_delay_100ms);
    }
}

void chegouMensagem(char *mensagem)
{
    char *msg;
    char *command;

    ESP_LOGI("The Picking Solution - MENSAGEM", "CHEGOU MENSAGEM");

    msg = str_part(mensagem, '.', 0);
    command = str_part(msg, ';', 0);

    ESP_LOGI("The Picking Solution - MENSAGEM", msg);

    boolean exec = checkAndDo_PICK(command, msg) || checkAndDo_CONFIRM(command, msg) || checkAndDo_REJECTED(command, msg) || checkAndDo_DONE(command, msg) || checkAndDo_APPROVE(command, msg) || checkAndDo_CANCEL(command, msg) || checkAndDo_ERROR(command, msg);

    //Libera memoria alocada !importante!
    str_part_free(msg);
    str_part_free(command);
}

boolean checkAndDo_PICK(char *command, char *msg)
{
    if (strcmp(command, "PICK") != 0 || logic_estado != LOGIC_ESPERANDO)
        return 0;
    logic_estado = LOGIC_SEPARANDO;
    //Pega valores da mesnagem
    logic_id = str_part(msg, ';', 1);
    char *LED_VERDE = str_part(msg, ';', 2);
    char *LED_VERMELHO = str_part(msg, ';', 3);
    char *qtd = str_part(msg, ';', 4);
    char *user = str_part(msg, ';', 5);

    //Converte valores
    logic_valor = atoi(qtd);
    logic_max_qty = logic_valor;

    int verde = atoi(LED_VERDE);
    int vermelho = atoi(LED_VERMELHO);

    //Mostra no LCD
    char *defStr = "                ;";
    char *l1 = str_part(defStr, ';', 0);
    for (int i = 0; i < 9; i++)
    {
        if (*(user + i) == '\0')
            break;
        l1[i] = user[i];
    }
    int qtyLen = strlen(qtd);
    int qtyPos = 16 - qtyLen;
    for (int i = qtyPos; i < 16; i++)
    {
        l1[i] = qtd[i - 15];
    }

    lcd_limpa();
    printLCD(l1, TRUE);
    printLCD("SEPARE          ", FALSE);

    //LEDs

    set_LED_VERMELHO(vermelho == 1);
    //set_LED_VERMELHO(verde == 1);

    // Limpa memoria alocada
    str_part_free(LED_VERDE);
    str_part_free(LED_VERMELHO);
    str_part_free(qtd);
    str_part_free(user);
    str_part_free(l1);
    return 1;
}

boolean checkAndDo_CONFIRM(char *command, char *msg)
{
    if (strcmp(command, "CONFIRM") != 0)
        return 0;
    return 1;
}

boolean checkAndDo_APPROVE(char *command, char *msg)
{
    if (strcmp(command, "APPROVE") != 0 || logic_estado != LOGIC_CONFIRMANDO)
        return 0;
    logic_estado = LOGIC_ESPERANDO;

    str_part_free(logic_id);
    logic_id = NULL;

    lcd_limpa();
    lcd_locate(0, 0);
    lcd_str("SUCESSO        ");

    set_LED_VERMELHO(FALSE);

    vTaskDelay(logic_task_delay_3s);

    if (logic_estado == LOGIC_ESPERANDO)
        lcd_limpa();

    return 1;
}

boolean checkAndDo_REJECTED(char *command, char *msg)
{
    if (strcmp(command, "REJECTED") != 0 || logic_estado != LOGIC_CONFIRMANDO)
        return 0;
    logic_estado = LOGIC_SEPARANDO;

    lcd_limpa();
    lcd_locate(0, 0);
    lcd_str("ERR AO CONFIRMAR");
    lcd_locate(1, 0);
    lcd_str("TENTE OUTRA VEZ ");
    return 1;
}

boolean checkAndDo_DONE(char *command, char *msg)
{
    if (strcmp(command, "DONE") != 0 || logic_estado != LOGIC_CONFIRMANDO)
        return 0;
    logic_estado = LOGIC_ESPERANDO;

    str_part_free(logic_id);
    logic_id = NULL;

    lcd_limpa();
    lcd_locate(0, 0);
    lcd_str("PICKING SEPARADO");

    set_LED_VERMELHO(FALSE);

    vTaskDelay(logic_task_delay_3s);

    if (logic_estado == LOGIC_ESPERANDO)
        lcd_limpa();

    return 1;
}

boolean checkAndDo_CANCEL(char *command, char *msg)
{
    if (strcmp(command, "CANCEL") != 0)
        return 0;
    logic_estado = LOGIC_ESPERANDO;

    if (logic_id != NULL)
    {
        str_part_free(logic_id);
        logic_id = NULL;
    }

    lcd_limpa();
    lcd_locate(0, 0);
    lcd_str("CANCELADO");

    vTaskDelay(logic_task_delay_3s);
    if (logic_estado == LOGIC_ESPERANDO)
        lcd_limpa();
    return 1;
}

boolean checkAndDo_ERROR(char *command, char *msg)
{
    if (strcmp(command, "ERROR") != 0)
        return 0;
    logic_estado = LOGIC_ESPERANDO;

    if (logic_id != NULL)
    {
        str_part_free(logic_id);
        logic_id = NULL;
    }

    char *error_msg = str_part(msg, ';', 2);
    lcd_limpa();
    lcd_locate(0, 0);
    lcd_str(error_msg);
    lcd_locate(1, 0);
    lcd_str("ERRO");

    vTaskDelay(logic_task_delay_3s);
    if (logic_estado == LOGIC_ESPERANDO)
        lcd_limpa();
    return 1;
}

void printLCD(char *message, boolean firstLine)
{
    lcd_locate(firstLine ? 0 : 1, 0);
    lcd_str(message);
}