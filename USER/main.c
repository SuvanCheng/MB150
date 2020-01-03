#include "stm32f10x.h"
#include "12864.h"
#include "delayy.h"
#include "MB150.h"
#include "delay.h"
#include "key.h"
#include "adc.h"
#include "dac.h"




int main(void)
{
		u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 dacval=160;
    u8 key=0;
    u16 a=2750;
    
    GPIO_LED_Configuration();// LED GPIO配置
    SystemInit(); //72MHz
    SendReferF( );//MB1504送基准数
	Adc_Init();		  		//ADC初始化
	Dac1_Init();				//DAC初始化
    Lcd_Init();
    delay_init();
    KEY_Init();//初始化与按键连接的硬件接口
    FrequenceToSend(a);///MB1504
    LCD12864_Write_SuperString(1,0,"K1+1Mhz K2-1Mhz");
    LCD12864_Write_SuperString(2,0,"K3+5Mhz K4-5Mhz");
    LCD12864_Write_Numberd(3,0,a);
    while(1)
    {
      key=KEY_Scan(0);//得到键值
      if(key)
          {
            switch(key)
                {

                case 4:	//按键4
                    a=a-50;
								key=0;
                    LCD12864_Write_Numberd(3,0,a);
                    if(a<2400)a=2400;
                    break;


                case 1:	//按键1
                    a=a+10;
                    FrequenceToSend(a);  ///MB1504
                    LCD12864_Write_Numberd(3,0,a);key=0;
                    if(a>3100)a=3100;
                    break;


                case 2:	//按键2

                    a=a-10;
                    FrequenceToSend(a);  ///MB1504
                    LCD12864_Write_Numberd(3,0,a);key=0;
                    if(a<2400)a=2400;
                    break;

                case 3:	//按键3
                    a=a+50;
                    FrequenceToSend(a);  ///MB1504
                    LCD12864_Write_Numberd(3,0,a);key=0;
                    if(a>3100)a=3100;
                    break;
								default : break;
                }
          }
      else delay_ms(100);
    }
}



