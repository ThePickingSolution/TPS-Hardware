#ifndef TPS_LCD
#define TPS_LCD

#include "datatypes.h"

void lcd_init();
void lcd_escreve_l1(char *mensagem);
void lcd_escreve_l2(char *mensagem);
void lcd_off();

typedef struct
{
    boolean rs;      //true = dados; false = comando
    boolean data[8]; //8bits de dados
} TpsLcd_t;

#endif // DATATYPES_H