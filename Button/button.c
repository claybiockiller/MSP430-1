#include <msp430.h> 
#include <intrinsics.h>

#define LED1 BIT0
#define LED2 BIT6
#define BUTTON BIT3


    int main(void)
    {
        WDTCTL = WDTPW + WDTHOLD; // 关闭看门狗
        P1DIR |= (LED1 + LED2); // 将LED设为输出
        P1REN |= BUTTON; // 允许使用上拉电阻
        P1OUT |= BUTTON; // 启用上拉电阻
        P1OUT &= ~(LED1 + LED2); // 关闭LED
       
        P1IES |= BUTTON; // 高电平到低电平
        P1IE |= BUTTON; // 允许中断
        P1IFG &= ~BUTTON; // 清除中断标志位

		__enable_interrupt();

        while(1);
    }

    __attribute__((interrupt(PORT1_VECTOR)))
    void PORT_1(void)
    {
        P1OUT ^= (LED1|LED2);
        P1IFG &= ~BUTTON;
		do P1IFG = 0;
		while( P1IFG != 0 );

    }
