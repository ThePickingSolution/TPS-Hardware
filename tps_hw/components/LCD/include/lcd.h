#define LCD_X 16
#define LCD_Y 2

#define LCD_D7 15
#define LCD_D6 13
#define LCD_D5 12
#define LCD_D4 14

#define LCD_RS 4
#define LCD_EN 5


#define LCD_LINE1 0x00
#define LCD_LINE2 0x40


#define LCDC_CLS            0x01
#define LCDC_HOME					  0x02
#define LCDC_ENTRY					0x04
	#define LCDC_ENTRYR				0x02
	#define LCDC_ENTRYL				0x00
	#define LCDC_MOVE					0x01
#define LCDC_ONOFF					0x08
	#define LCDC_DISPLAYON		0x04
	#define LCDC_CURSORON			0x02
	#define LCDC_CURSOROFF		0x00
	#define LCDC_BLINKON			0x01
#define LCDC_SHIFT					0x10
	#define LCDC_SHIFTDISP		0x08
	#define LCDC_SHIFTR				0x04
	#define LCDC_SHIFTL				0x00
#define LCDC_FUNC					  0x20
	#define LCDC_FUNC8B				0x10
	#define LCDC_FUNC4B				0x00
	#define LCDC_FUNC2L				0x08
	#define LCDC_FUNC1L				0x00
	#define LCDC_FUNC5x10			0x04
	#define LCDC_FUNC5x7			0x00
#define LCDC_SET_CGRAM			0x40
#define LCDC_SET_DDRAM			0x80


#define RS_HIGH gpio_set_level(LCD_RS, 1)
#define RS_LOW gpio_set_level(LCD_RS, 0)
#define EN_HIGH gpio_set_level(LCD_EN, 1)
#define EN_LOW gpio_set_level(LCD_EN, 0)


void LCD_sendHalf(unsigned char data);
void LCD_sendByte(unsigned char data);
void LCD_cmd(unsigned char cmd);
void LCD_data(unsigned char data);
void LCD_init();
void LCD_cls();
void lcd_locate(unsigned char x, unsigned char y);
void lcd_str(char * str);
