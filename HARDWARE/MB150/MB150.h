//-----------------------------------------------------------------
// LED驱动头文件
// 头文件名: LED.h
// 作    者: 凌智电子
// 开始日期: 2014-01-28
// 完成日期: 2014-01-28
// 修改日期: 2014-02-16
// 当前版本: V1.0.1
// 历史版本:
//   - V1.0: (2014-02-07)LED IO 配置
// - V1.0.1:(2014-02-16)头文件中不包含其他头文件
//-----------------------------------------------------------------

#ifndef _MB150_H
#define _MB150_H
#define uchar unsigned char
#define uint unsigned int
//-----------------------------------------------------------------
// 位操作
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
// 外部函数声明
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
