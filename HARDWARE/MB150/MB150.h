//-----------------------------------------------------------------
// LED����ͷ�ļ�
// ͷ�ļ���: LED.h
// ��    ��: ���ǵ���
// ��ʼ����: 2014-01-28
// �������: 2014-01-28
// �޸�����: 2014-02-16
// ��ǰ�汾: V1.0.1
// ��ʷ�汾:
//   - V1.0: (2014-02-07)LED IO ����
// - V1.0.1:(2014-02-16)ͷ�ļ��в���������ͷ�ļ�
//-----------------------------------------------------------------

#ifndef _MB150_H
#define _MB150_H
#define uchar unsigned char
#define uint unsigned int
//-----------------------------------------------------------------
// λ����
//-----------------------------------------------------------------
#define CLK_0 		GPIO_ResetBits(GPIOC,GPIO_Pin_0)
#define CLK_1 		GPIO_SetBits(GPIOC,GPIO_Pin_0)
#define DATA_0	  GPIO_ResetBits(GPIOC,GPIO_Pin_2)
#define DATA_1    GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define LE_0		  GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define LE_1      GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define KEY1 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY2 			GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY3 			GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEY4 			GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)

//-----------------------------------------------------------------
// �ⲿ��������
//-----------------------------------------------------------------
extern void GPIO_LED_Configuration(void);
extern void Send16Bit( uint SendData);
extern void Send11Bit( uint SendData ) ;  
extern void Send8Bit( uchar SendData ) ; 
extern void SendReferF( void )  ;
extern void FrequenceToSend( uint FrequenceD ); 
extern void GPIO_Keyboard_Configuration(void);

#endif

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
