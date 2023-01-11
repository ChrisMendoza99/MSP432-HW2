#include "msp.h"
#define ONE_SEC 2130000 //becasue im lazy and wanted to be cool
//The pointer is used to change the value of the constant integer


void toaster_one()
{

    P2->OUT = BIT1;
    __delay_cycles(4260000); //delayed for 2 seconds
    P2->OUT &= ~BIT1;
    P2->OUT = 0x0C;
    __delay_cycles(ONE_SEC); //delayed for 2 seconds
    P2->OUT &= ~0x0C;
}
void toaster_two()
{
    P2->OUT = BIT1;
    __delay_cycles(6390000); //delayed for 2 seconds
    P2->OUT &= ~BIT1;
    P2->OUT = 0x0C;
    __delay_cycles(ONE_SEC); //delayed for 2 seconds
    P2->OUT &= ~0x0C;
}
void toaster_three()
{

    P2->OUT = BIT1;
    __delay_cycles(8520000); //delayed for 2 seconds
    P2->OUT &= ~BIT1;
    P2->OUT = 0x0C;
    __delay_cycles(ONE_SEC); //delayed for 2 seconds
    P2->OUT &= ~0x0C;
}
void toaster_four()
{

    P2->OUT = BIT1;
    __delay_cycles(10650000); //delayed for 2 seconds
    P2->OUT &= ~BIT1;
    P2->OUT = 0x0C;
    __delay_cycles(ONE_SEC); //delayed for 2 seconds
    P2->OUT &= ~0x0C;
}


void PORTINIT()
{
    /*Input Interrupt*/
    P2->DIR = 0xF0; //Setting as Inputs
    P2->REN = 0xF0; //Enabling Resistors as pull
    P2->OUT = 0xF0; //P4.0 -> P4.3 are set as Pull Up
    P2->IES = 0xF0; //Detects on the falling edge
    P2->IFG = 0; //flag clear
    P2->IE = 0xF0;
    NVIC->IP[36] = 0x09;
    NVIC->ISER[1] |= BIT4;
    /*Outputs*/
    P2->DIR = 0x0E; //Setting P2.3 and P2.4 as Outputs
    P2->OUT = 0x0E;
    P2->OUT &= ~0x0E;
}

void PORT2_IRQHandler()
{
    if(P2->IN & BIT4){}
    else
    {
        toaster_one();
    }
    if(P2->IN & BIT5){}
    else
    {
        toaster_two();
    }
    if(P2->IN & BIT6){}
    else
    {
        toaster_three();
    }
    if(P2->IN & BIT7){}
    else
    {
        toaster_four();
    }
    //SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
    P2->IFG = 0;
}


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    PORTINIT();
    //SysTick_Init();
    __enable_irq();// Enable global interrupt
        //While there is no decision making, the device will be asleep
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    __DSB();
    __WFI();

}
