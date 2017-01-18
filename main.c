/*
 */

#include "config.h"

extern unsigned char CanReceiveEndFlag;

int main(void)
{
    struct MOb msg={0x18B20013,{1,3,7,6,0,7,0,0}};
    // Insert code
    GPIOD_init();
    InitCAN();
    //PORTD = 0xff;
    //DDRD  = 0xa9;
    GPIOF_PIN1_OUTPUT;
    GPIOF_PIN1_DATA = 1;
    // MOB_send();
    sei();
    CANGIE |= 1<<ENRX;

    while (1)
    {
      	//Place your code here
        //if(CanReceiveEndFlag==1)
        //  {
        //     _delay_ms(1);
        //     GPIOF_PIN1_DATA = 0;
        //     MOB_send();
        //     CanReceiveEndFlag=0;
		//  }
		can_tx(msg);
		_delay_ms(1000);
      	/*GPIOD_PIN5_DATA = 0;
		_delay_ms(1000);
		GPIOD_PIN6_DATA = 0;
		_delay_ms(1000);
		GPIOD_PIN5_DATA = 1;
		_delay_ms(1000);
		GPIOD_PIN6_DATA = 1;
		_delay_ms(1000);*/

    };

    return 0;
}
