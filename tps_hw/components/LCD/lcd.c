#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "lcd.h"
#include "esp_log.h"

void enable_pulse(void)
{
  EN_LOW;
  os_delay_us(1);
  EN_HIGH;
  os_delay_us(1);
  EN_LOW;
  os_delay_us(100);
}

void LCD_sendHalf(unsigned char data)
{
  if (data & (1 << 0))
    gpio_set_level(LCD_D4, 1);
  else
    gpio_set_level(LCD_D4, 0);

  if (data & (1 << 1))
    gpio_set_level(LCD_D5, 1);
  else
    gpio_set_level(LCD_D5, 0);

  if (data & (1 << 2))
    gpio_set_level(LCD_D6, 1);
  else
    gpio_set_level(LCD_D6, 0);

  if (data & (1 << 3))
    gpio_set_level(LCD_D7, 1);
  else
    gpio_set_level(LCD_D7, 0);
}

void LCD_sendByte(unsigned char data)
{
  EN_HIGH;
  LCD_sendHalf(data >> 4);
  EN_LOW;

  EN_HIGH;
  LCD_sendHalf(data);
  EN_LOW;
  os_delay_us(120);
}

void LCD_cmd(unsigned char cmd)
{
  RS_LOW;
  LCD_sendByte(cmd);
}

void LCD_data(unsigned char data)
{
  RS_HIGH;
  LCD_sendByte(data);
}

void LCD_cls(void)
{
  LCD_cmd(0x01);
}

void LCD_init()
{
  os_delay_us(15000);
  EN_HIGH;
  LCD_sendHalf(0x03);
  EN_LOW;
  os_delay_us(4100);
  EN_HIGH;
  LCD_sendHalf(0x03); // 2x
  EN_LOW;
  os_delay_us(100);
  EN_HIGH;
  LCD_sendHalf(0x03); // 3x
  EN_LOW;
  os_delay_us(100);
  EN_HIGH;
  LCD_sendHalf(0x02); // Wybranie juz trybu 4-bitowego
  EN_LOW;
  os_delay_us(100);

  LCD_cmd(LCDC_FUNC | LCDC_FUNC4B | LCDC_FUNC2L | LCDC_FUNC5x7);
  LCD_cmd(LCDC_ONOFF | LCDC_CURSOROFF);
  LCD_cmd(LCDC_ONOFF | LCDC_DISPLAYON);
  LCD_cmd(LCDC_ENTRY | LCDC_ENTRYR);
}

// Send string to screen
void lcd_str(char *str)
{
  while (*str)
    LCD_data(*str++);
  ESP_LOGI("The Picking Solution - LCD", str);
}

// Locate cursor position
void lcd_locate(unsigned char x, unsigned char y)
{
  unsigned char xy = y + x * 0x40;
  LCD_cmd((xy | 0x80));
}

void lcd_limpa()
{
  lcd_locate(1, 0);
  lcd_str("                ");
  lcd_locate(0, 0);
  lcd_str("                ");
  lcd_locate(0, 0);
}
