#include "MatrixKey.h"
#include "delay.h"
void MatrixKey_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
   GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
   GPIO_Init(GPIOE,&GPIO_InitStructure);
}
u8 MatrixKey_Scan(void)
{
    if((KEY0==0)||(KEY1==0)||(KEY2==0)||(KEY3==0))
	{
	  delay_ms(20);
	  if(KEY0==0){while(KEY0==0);return 1;}
	  else if(KEY1==0){while(KEY1==0);return 2;}
	  else if(KEY2==0){while(KEY2==0);return 3;}
	  else if(KEY3==0){while(KEY3==0);return 4;}
	}
	return 0;
}
//行置为输入 默认为1 列置为输出默认为0	扫描行 
void HL_Init_HScan(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
     GPIO_InitStructure.GPIO_Pin=HPin;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	 GPIO_Init(GPIOD,&GPIO_InitStructure); 

	 GPIO_InitStructure.GPIO_Pin=LPin;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init(GPIOD,&GPIO_InitStructure); 
	 GPIO_ResetBits(GPIOD,LPin);
}
//行置为输出 默认为0 列置为输入默认为1	扫描列 
void HL_Init_LScan(void)
{
     GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
     GPIO_InitStructure.GPIO_Pin=LPin;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	 GPIO_Init(GPIOD,&GPIO_InitStructure); 

	 GPIO_InitStructure.GPIO_Pin=HPin;
	 GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init(GPIOD,&GPIO_InitStructure); 
	 GPIO_ResetBits(GPIOD,HPin);


}
u8 MatrixKey_Scan(void)
{
    u16 temp=0;
	u8 key=0;
	HL_Init_HScan();
	temp=GPIO_ReadInputData(GPIOD);
    temp&=0x000f; //得到低四位数据 检测4个2进制数中0的存在
	if(temp==0x0e)//第一行有按键被按下
	{
	  key=1	;
	}
	else if(temp==0x0d)
	{
	  key=2;
	}
	else if(temp==0x0b)
	{
	  key=3;
	}
	else if(temp==0x07)
	{
	  key=4;
	}else key=0;

   HL_Init_LScan();
   temp=GPIO_ReadInputData(GPIOD);
   temp&=0x00f0;//得到高四位 即列数据 
   if((temp==0xe0)&&(key!=0))//第一列被按下
   {
      key=(key-1)*4+1;
   }else
   if((temp==0xd0)&&(key!=0))
   {
      key=(key-1)*4+2;
   }else
   if((temp==0xb0)&&(key!=0))
   {
     key=(key-1)*4+3;
   }else
   if((temp==0x70)&&(key!=0))
   {
     key=(key-1)*4+4;
   }
   else key=0;
  
   return key;
}










