#ifndef __MATRIXKEY_H
#define __MATRIXKEY_H
#include "sys.h"
#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEY2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY3 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)


#define HPin  GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_1|GPIO_Pin_0
#define LPin  GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4
//#define HRead();  GPIO_ReadInputData(GPIOD);
//#define LRead();  GPIO_ReadInputData(GPIOD);
void MatrixKey_Init(void);
u8 MatrixKey_Scan(void);

void HL_Init_HScan(void);
void HL_Init_LScan(void);

u8 MatrixKey_Scan(void);
#endif
