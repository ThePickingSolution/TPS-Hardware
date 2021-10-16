#include "tps_lcd.h"
#include "datatypes.h"
#include "hal.h"

#define LCD_CMD_DISPLAY_OFF 0x08
#define LCD_CMD_DISPLAY_ON 0X0F

#define LCD_CMD_LINE1 0x80
#define LCD_CMD_LINE2 0xC0

#define LCD_CMD_CLEAR 0x01
#define LCD_CMD_RETURN_HOME 0x02

#define LCD_CMD_INC_CURSOR 0x06
#define LCD_CMD_DEC_CURSOR 0x04

#define LCD_CMD FALSE
#define LCD_DATA TRUE

boolean lcd_is_on;

void lcd_on();
void lcd_off();
void lcd_limpar();
void lcd_inicio_l1();
void lcd_inicio_l2();
void lcd_move_cursor(boolean right);
void lcd_execute(boolean isdata, uint8 instruction);
void lcd_set_data(TpsLcd_t *lcd, uint8 instruction);

void lcd_init()
{
    //lcd_execute(LCD_CMD,0x28);
    lcd_limpar();
    lcd_off();

    lcd_on();
}

void lcd_escreve_l1(char *mensagem)
{
    lcd_inicio_l1();
    //printf(mensagem);
}

void lcd_escreve_l2(char *mensagem)
{
    lcd_inicio_l2();
    //printf(mensagem);
}

//Desliga tela do LCD
void lcd_on()
{
    if (lcd_is_on)
        return;
    lcd_execute(LCD_CMD, LCD_CMD_DISPLAY_ON);
    lcd_is_on = TRUE;
}

//Desliga tela do LCD
void lcd_off()
{
    lcd_execute(LCD_CMD, LCD_CMD_DISPLAY_OFF);
    lcd_is_on = FALSE;
}

//Limpa o display
void lcd_limpar()
{
    lcd_execute(LCD_CMD, LCD_CMD_CLEAR);
}

void lcd_inicio_l1()
{
    lcd_limpar();
    lcd_execute(LCD_CMD, LCD_CMD_LINE1);
    lcd_execute(LCD_CMD, LCD_CMD_RETURN_HOME);
    lcd_on();
}

void lcd_inicio_l2()
{
    lcd_limpar();
    lcd_execute(LCD_CMD, LCD_CMD_LINE2);
    lcd_execute(LCD_CMD, LCD_CMD_RETURN_HOME);
    lcd_on();
}

void lcd_move_cursor(boolean right)
{
    if (right)
    {
        lcd_execute(LCD_CMD, LCD_CMD_INC_CURSOR);
    }
    else
    {
        lcd_execute(LCD_CMD, LCD_CMD_DEC_CURSOR);
    }
}

//Converte informação e envia para o hal onde coloca nos pinos
void lcd_execute(boolean isdata, uint8 instruction)
{
    TpsLcd_t lcd;
    lcd.rs = isdata;
    lcd_set_data(&lcd, instruction);
    envia_display(lcd.rs, lcd.data);
}

//Converte comando em bits
void lcd_set_data(TpsLcd_t *lcd, uint8 instruction)
{
    lcd->data[0] = ((instruction >> 0) & 0x01) ? TRUE : FALSE;
    lcd->data[1] = ((instruction >> 1) & 0x01) ? TRUE : FALSE;
    lcd->data[2] = ((instruction >> 2) & 0x01) ? TRUE : FALSE;
    lcd->data[3] = ((instruction >> 3) & 0x01) ? TRUE : FALSE;
    lcd->data[4] = ((instruction >> 4) & 0x01) ? TRUE : FALSE;
    lcd->data[5] = ((instruction >> 5) & 0x01) ? TRUE : FALSE;
    lcd->data[6] = ((instruction >> 6) & 0x01) ? TRUE : FALSE;
    lcd->data[7] = ((instruction >> 7) & 0x01) ? TRUE : FALSE;
}