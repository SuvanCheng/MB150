#ifndef __12864_H          
#define __12864_H

void Lcd_Init(void);

void SendByte(unsigned char Dbyte);
void Lcd_Write_Cmd(unsigned char Cbyte);
void Lcd_Write_Data(unsigned char Dbyte);

void LCD12864_Clear();
void LCD12864_Write_SuperString(unsigned char x,unsigned char y,unsigned char *s);
void LCD12864_Write_Numberd(unsigned char X,unsigned char Y,int number);
void LCD12864_Write_Numberf(unsigned char X,unsigned char Y,float number);
void LCD_Set_XY(unsigned char x,unsigned char y); 

void Lcd_Fill(unsigned char color); 
#endif

