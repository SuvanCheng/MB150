//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include <stm32f10x.h>
#include "MB150.h"
#include "delayy.h"

//-----------------------------------------------------------------
// 初始化程序区
// void GPIO_LED_Configuration(void)
//-----------------------------------------------------------------
//
// 函数功能: LED GPIO配置
// 入口参数: 无
// 返 回 值: 无
// 全局变量: 无
// 调用模块: RCC_APB2PeriphClockCmd();GPIO_Init();
// 注意事项: 无
//
//-----------------------------------------------------------------
void GPIO_LED_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;// 使能IO口时钟
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);//PC0 =	CLK	  PC2 = DATA		PC4 = LE
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2| GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Send16Bit(uint SendData)
{
    uchar i;
    uint SendMiddle;
    SendMiddle=SendData;
    LE_0;
    CLK_0;
    for(i=0; i<16; i++)
        {
            if((SendMiddle & 0x8000)==0x8000)
                {
                    DATA_1;
                }
            else
                {
                    DATA_0;
                }
            Delay_1us (2);
            CLK_1;
            Delay_1us (2);
            CLK_0;
            SendMiddle= SendMiddle<<1;
        }
    LE_1;
    Delay_1us (2);
    LE_0;
}

void Send11Bit(uint SendData)
{
    uchar i;
    LE_0;
    CLK_0;
    for( i = 0; i < 11; i ++ )
        {
            if((SendData & 0x8000)==0x8000)
                {
                    DATA_1;
                }
            else
                {
                    DATA_0;
                }
            Delay_1us (2);
            CLK_1;
            Delay_1us (2);
            CLK_0;
            SendData = SendData << 1;
        }
}

void Send8Bit( uchar SendData )
{
    uchar i;
    for( i = 0; i < 8; i ++ )
        {
            if((SendData & 0x80)==0x80)
                {
                    DATA_1;
                }
            else
                {
                    DATA_0;
                }
            Delay_1us (2);
            CLK_1;
            Delay_1us (2);
            CLK_0;
            SendData = SendData << 1;
        }
    LE_1;
    Delay_1us (2);
    LE_0;
}

void SendReferF( void )
{
    //针对警惕采用12M
    Send16Bit( 0x80f1 ); // 12M Crystal   100K
//	 Send16Bit( 0x81e1 ); // 12M Crystal   50K
//  Send16Bit( 0x8079 ); // 12M Crystal   200K
//	Send16Bit( 0x8961 ); // 12M Crystal   10K

}

void FrequenceToSend( uint FrequenceD )
{
    uchar AD = 0;
    uint  ND = 0;
    uint MiddleF = 2000;

//  if( ( FrequenceD >= 800 ) && ( FrequenceD <= 6000 ) )
//  {                   // 限制    锁定频率范围
    MiddleF = FrequenceD;
    ND = ( uint  ) ( MiddleF / 32 );
    AD = ( uchar ) ( MiddleF % 32 );
    ND = ND << 5;
    AD = AD << 1;
    AD = AD & 0xfe;
    Send11Bit( ND );
    Send8Bit( AD );
//  }
}


void GPIO_Keyboard_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;    //键盘输入IO口初始化程序
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE ,ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
