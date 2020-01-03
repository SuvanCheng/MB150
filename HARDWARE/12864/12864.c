#include "stm32f10x.h"
#include "12864.h"
#include "delay.h"
#include <stdio.h>
/****************************************
12864���������ô��нӷ�
****************************************/
typedef unsigned char uchar;
typedef unsigned int  unit;  //�궨��

/*�⺯����ʽ
#define   LCD_PSB_0       GPIO_ResetBits(GPIOB,GPIO_Pin_12) //����PSB����
#define   LCD_RS_1	      GPIO_SetBits(GPIOB,GPIO_Pin_15) //Ƭ��RS����
#define   LCD_SCLK_0      GPIO_ResetBits(GPIOB,GPIO_Pin_13)  //EN����Ϊʱ��
#define   LCD_SCLK_1      GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define   LCD_SID_0       GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define   LCD_SID_1       GPIO_SetBits(GPIOB,GPIO_Pin_14)//RW����Ϊ���ݣ�����Ϊ��д
*/
#define   LCD_PSB_0       GPIOB->ODR &=~(1<<12)  //����ת��Ҳ����ֱ�ӽӵ�
#define   LCD_RS_1	      GPIOB->ODR |= (1<<15)		//Ҳ����ֱ��������Ƭѡ
#define   LCD_SCLK_0      GPIOB->ODR &=~(1<<13)
#define   LCD_SCLK_1      GPIOB->ODR |= (1<<13)	//����EN�������б�ΪSCLK
#define   LCD_SID_0       GPIOB->ODR &=~(1<<14)
#define   LCD_SID_1       GPIOB->ODR |= (1<<14) //����RW�ڴ����оͱ�ΪSID
/******************LCD���ܳ�ʼ��ָ��--���ã����ο�**********************************
#define CLEAR_SCREEN 0x01   //����ָ�������ACֵΪ00H
#define AC_INIT      0x02   //��AC����Ϊ00H�����α��Ƶ�ԭ��λ��
#define CURSE_ADD    0x06   //�趨�α��Ƶ�����ͼ�������ƶ�����Ĭ���α����ƣ�ͼ�����岻����
#define FUN_MODE     0x30   //����ģʽ��8λ����ָ�
#define DISPLAY_ON   0x0c   //��ʾ��,��ʾ�α꣬���α�λ�÷���
#define DISPLAY_OFF  0x08   //��ʾ��
#define CURSE_DIR    0x14   //�α������ƶ�:AC=AC+1
#define SET_CG_AC    0x40   //����AC����ΧΪ��00H~3FH
#define SET_DD_AC    0x80
#define MAP_ON       0x36   //ͼ����ʾ��
#define MAP_OFF      0x34   //ͼ����ʾ��
*********************************************************************************/

void Lcd_Init(void)
{
    /* �⺯����ʽ
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);//ʹ�ܶ˿�ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//�˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);	//�����趨������ʼ��GPIO
    GPIO_SetBits(GPIOA,GPIO_Pin_0);//�����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//�˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO
    GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);//�����
    */
    RCC->APB2ENR |= 1<<2; //ʹ��PAʱ��
    RCC->APB2ENR |= 1<<3; //ʹ��PBʱ��
    GPIOA->CRL &= 0XFFFFFFF0;
    GPIOA->CRL |= 0X00000003; //PA.0�������
    GPIOA->ODR |= 1<<0;       //PA.0���1
    GPIOB->CRH &= 0X0000FFFF;
    GPIOB->CRH |= 0X33330000; //PB.12/13/14/15�������
    GPIOB->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);//���1

    LCD_PSB_0; //һֱ���ͣ��ô��ڷ�ʽ���� ����ֱ�ӽӵأ�
    LCD_RS_1;  //CSһֱ���ߣ�ʹ��Һ������ֱ�ӽ�VCC��

    Lcd_Write_Cmd(0x30);
    delay_us(10000);
    Lcd_Write_Cmd(0x01);
    delay_us(10000);
    Lcd_Write_Cmd(0x02);
    delay_us(10000);
    Lcd_Write_Cmd(0x06);
    delay_us(10000);
    Lcd_Write_Cmd(0x0c);
    delay_us(10000);
    Lcd_Write_Cmd(0x34); //ͼ�ο���������ʾ��
    delay_us(10000);
    Lcd_Fill(0x00);    //�������RAM
    delay_us(10000);
    Lcd_Write_Cmd(0x36); //ͼ�ο���������ʾ��
    delay_us(10000);
}

void SendByte(uchar Dbyte)
{
    uchar i;
    for(i=8; i>0; i--)
        {
            if (Dbyte&0x80)  LCD_SID_1;//ȡ�����λ
            else LCD_SID_0;
            LCD_SCLK_1;  //�����ʾ�����⣬�����ڴ˺���ӳ�
            delay_us(1); //72MHZ�ٶ�̫�죬M0��48MHZ�������
            LCD_SCLK_0;
            Dbyte<<=1;
        }
}
void Lcd_Write_Cmd(uchar Cbyte )
{
    //LCD_RS_1;
    SendByte(0xf8);              //11111,RW(0),RS(0),0
    SendByte(0xf0&Cbyte);
    SendByte(0xf0&Cbyte<<4);
    //LCD_RS_0;
}

void Lcd_Write_Data(uchar Dbyte )
{
    //LCD_RS_1;
    SendByte(0xfa);              //11111,RW(0),RS(1),0
    SendByte(0xf0&Dbyte);
    SendByte(0xf0&Dbyte<<4);
    //LCD_RS_0;
}

void LCD_Set_XY(uchar x,uchar y)
{
    unsigned char k = 0;
    switch(x)
      {
        case 1:k  = 0x80 + y;break;
        case 2:k  = 0x90 + y;break;
        case 3:k  = 0x88 + y;break;
        case 4:k  = 0x98 + y;break;
        default:k = 0x80 + y;
      }
    Lcd_Write_Cmd(k);
}

void LCD12864_Clear()
{
	LCD12864_Write_SuperString(1,0,"                      ");
	LCD12864_Write_SuperString(2,0,"                      ");
	LCD12864_Write_SuperString(3,0,"                      ");
	LCD12864_Write_SuperString(4,0,"                      ");
  Lcd_Write_Cmd(0x01);
  delay_us(10000);
}
void LCD12864_Write_SuperString(uchar x,uchar y,uchar *s)
{
    Lcd_Write_Cmd(0x30); //�����׼ģʽ
    LCD_Set_XY(x,y);
    while (*s)
        {
            Lcd_Write_Data(*s);
            s++;
        }
    Lcd_Write_Cmd(0x36); //����ͼ��ģʽ
}
void LCD12864_Write_Numberd(unsigned char X,unsigned char Y,int number)
{
	char sz[8];//�ַ���
	sprintf(sz, "%d", number);//�����Ҫͷ�ļ�#include <stdio.h>
  LCD12864_Write_SuperString(X,Y,sz);
}
void LCD12864_Write_Numberf(unsigned char X,unsigned char Y,float number)
{
	char sz[8];//�ַ���
	sprintf(sz, "%f", number);//�����Ҫͷ�ļ�#include <stdio.h>
  LCD12864_Write_SuperString(X,Y,sz);
}


void Lcd_Fill(uchar color) //�������RAM
{
    uchar x,y,i;
    Lcd_Write_Cmd(0x34);
    for(i=0; i<9; i=i+8)
        for(y=0; y<0x20; y++)
            {
                for(x=0; x<8; x++)
                    {
                        Lcd_Write_Cmd(y+0x80);
                        Lcd_Write_Cmd(x+0x80+i);
                        Lcd_Write_Data(color);
                        Lcd_Write_Data(color);
                    }
            }
    Lcd_Write_Cmd(0x36);
}
/*******************************************************************************
LCD12864�ӿڶ������£�
����ģʽ���£�
 
��1�ţ� VSSΪ�ص�Դ
��2�ţ� VDD��5V����Դ
��3�ţ� V0ΪҺ����ʾ���Աȶȵ����ˣ�������Դʱ�Աȶ��������ӵص�Դʱ�Աȶ����
��4�ţ� RSΪ�Ĵ���ѡ�񣬸ߵ�ƽʱѡ�����ݼĴ������͵�ƽʱѡ��ָ��Ĵ�����
��5�ţ� R/W  ��R/W��E��Ϊ�ߵ�ƽʱ�����ݱ�����DB0��DB7����R/WΪ�͵�ƽ��E�Ӹߵ�ƽ��Ϊ�͵�ƽ��DB0��DB7�����ݱ�д��IR��DR�Ĵ�����
��6�ţ� E  ʹ���ź�
��7~14�ţ�DB0��DB7  Ϊ8λ˫�������ߡ�
��15�ţ�PSB  ����/����ѡ�񡣵�PSBΪ�ߵ�ƽʱ�ǲ���ģʽ����PSBΪ�͵�ƽʱ���Ǵ���ģʽ����
��16�ţ�NC  �սš�
��17�ţ�/RESET ��λ�š��͵�ƽ�н���
��18�ţ�VOUT  LCD������ѹ����ˣ��ɲ��ӡ�
��19�ţ�A  ����Ƶ�Դ��������+5V��
��20�ţ�K  ����Ƶ�Դ�������ӵء�

����ģʽ���£�
 
��1�ţ� VSSΪ�ص�Դ
��2�ţ� VDD��5V����Դ
��3�ţ� V0ΪҺ����ʾ���Աȶȵ����ˣ�������Դʱ�Աȶ��������ӵص�Դʱ�Աȶ����
��4�ţ� CS  Ƭѡ�źţ��ߵ�ƽ��Ч��
��5�ţ� SID  ������������ˡ�
��6�ţ� CLK  ����ͬ��ʱ�ӡ�
��15�ţ�PSB  ����/����ѡ�񡣵�PSBΪ�ߵ�ƽʱ�ǲ���ģʽ����PSBΪ�͵�ƽʱ���Ǵ���ģʽ��
��17�ţ�/RESET ��λ�š��͵�ƽ�н���
��19�ţ�A  ����Ƶ�Դ��������+5V��
��20�ţ�K  ����Ƶ�Դ�������ӵ�?
*******************************************************************************/