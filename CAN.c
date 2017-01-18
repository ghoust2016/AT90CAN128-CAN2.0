/*
*/
#include "config.h"

unsigned char can_transdata[8]={1,2,3,4,5,6,7,8};
unsigned char can_receivedata[8]={8,7,6,5,4,3,2,1};
unsigned char CanReceiveEndFlag = 0;

unsigned char msg_tmp[8];

/****************************************************************/
/* CAN initialization                                                */
/****************************************************************/

void InitCAN(void)
{
// CAN������ 0# ,3# �����жϽ��� ��1#��2#��4# ���䷢������
  CANGCON |= (1<<SWRES);    //CAN��������λ
  //CANBT1 = 0x06;            //���ò����ʷ�Ƶ����16MHz,16TQ,250k,=4=3+1,3
  //CANBT2 = 0x0c;            //ͬ����Ϊ1��0x0n��������=7=6+1
  //CANBT3 = 0x37;            //��λ����PH2=4=3+1��PH1=4=3+1
  CANBT1 = 0x0E;            //���ò����ʷ�Ƶ����16MHz,16TQ,250k,=4=3+1,3
  CANBT2 = 0x04;            //ͬ����Ϊ1��0x0n��������=7=6+1
  CANBT3 = 0x13;            //��λ����PH2=4=3+1��PH1=4=3+1
  CANTCON = 0xff;
//--------------can_MOB INITIAL-------------------
//MOB0=RX[CMD]    ������λ��������ָ��       ��ʽ��3,0,0,177,239,33
  CANPAGE  = 0x00;          //MOB0,�Զ���������ֵΪ0
  CANSTMOB = 0;
  CANCDMOB = 0x18;          //can2B,DLC=8
  CANIDT4 = 0x30;           // 00001 0xx
  CANIDT3 = 0x00;           // 01111 001              33
  CANIDT2 = 0x41;           // 10001 111             239
  CANIDT1 = 0x00;           // 01100 101             177
  CANIDM4  = 0x00;          // 11111 100
  CANIDM3  = 0x00;          // 11111 111
  CANIDM2  = 0x00;          // 11111 111
  CANIDM1  = 0x00;
                                                               //CANIDM4-1����У�����μĴ���  00000 111
  //MOB1=TX[STA1]  ����λ������״̬��1          6,0,0,178,239,33
  CANPAGE = 0x10;
  CANSTMOB = (1<<TXOK);
  CANCDMOB = 0x18;
  CANIDT4 = 0x30;                       // 00001 000
  CANIDT3 = 0x80;                       // 01111 001              33
  CANIDT2 = 0x00;                       // 10010 111             239
  CANIDT1 = 0x20;                       // 11000 101             178

  CANGIE |= ((1<<ENIT) + (1<<ENRX));    //��ȫ���ж� �� �����ж�
  CANIE2 |= 0x09;                       //��MOB3 & MOB0��������ж�(��������)
  CANPAGE = 0x00;
  CANCDMOB |= 0x80;                     //MOB0����ʹ��  //MOB3����ʹ��
  CANGCON |= 0x02;                      //CAN����������
}

/*�жϺ���     ����CAN����֡ �� �������ݵ�Ԫ�� */

SIGNAL( CANIT_vect )
{
    //GPIOF_PIN1_DATA = 0;
    unsigned char num_i;
    CANGIE &= ~(1<<ENRX);                  //�ؽ����ж�****
    CANPAGE = 0x00;
    for(num_i = 0; num_i < 8; num_i++)
    {
      can_receivedata[num_i]=CANMSG;       //ȡ��8���ֽڵ�����
    }

    CANPAGE = 0x00;
    CANSTMOB &= ~(1<<RXOK);                //���жϱ�־****
    CANCDMOB = 0x98;                       //����ʹ��
    CANGIE |= (1<<ENRX);                   //���ж�
    CanReceiveEndFlag=1;
}

/*CAN����֡���� */

void MOB_send(void)
{
  CANGIE &= ~(1<<ENRX);

  unsigned int i;
  //GPIOF_PIN1_DATA = 0;
  CANPAGE = 0x10;                        //MOB1, auto increment, index 0
  if (CANSTMOB & (1<<TXOK))
  {
 // CANCDMOB= 0x18;
  CANSTMOB &= ~(1<<TXOK);

  for(i = 0; i < 8; i++)
  {
   CANMSG = can_transdata[i];
  }
  CANCDMOB = 0x58;

  CANGIE |=(1<<ENRX);
  }
}

/* CAN transmission via mailbox 1 (polling)                        */
/****************************************************************/
void can_tx(struct MOb msg)
{
	unsigned char i=0;

	CANSTMOB=0;
	//enable MOb1, auto increment index, start with index = 0
	CANPAGE = (1<<4);

	//set IDE bit, length = 8
	CANCDMOB = (1<<IDE) | (8<<DLC0);

	//write 29 Bit identifier
	msg.id <<= 3;
	CANIDT4 = (unsigned char) (msg.id&0xF8);
	CANIDT3 = (unsigned char) (msg.id>>8);
	CANIDT2 = (unsigned char) (msg.id>>16);
	CANIDT1 = (unsigned char) (msg.id>>24);

	//put data in mailbox
	for (i=0; i<8; i++)
		CANMSG = msg.data[i];

	//enable transmission
	CANCDMOB |= (1<<CONMOB0);

	//wait until complete
	while (!(CANSTMOB & (1<<TXOK)));

	//reset flag
	CANSTMOB &= ~(1<<TXOK);
}


/****************************************************************/
/* CAN reception evia mailbox 0 (polling)                        */
/****************************************************************/
void can_rx(struct MOb msg)
{
	unsigned char i;

	CANHPMOB=0;

	//select MOb0
	CANPAGE = 0x00; 	   //select MOb0

	//clear MOb flags
	CANSTMOB = 0;

	msg.id=2;

	//select ID which can be receive
	CANIDT4 = (uint8_t) (msg.id << 3);
	CANIDT3 = (uint8_t) (msg.id >> 5);
	CANIDT2 = (uint8_t) (msg.id >> 13);
	CANIDT1 = (uint8_t) (msg.id >> 21);

	// set mask in order to receive only the message with the ID
	CANIDM4 = 248;
	CANIDM3 = 255;
	CANIDM2 = 255;
	CANIDM1 = 255;
	// enable extended ID
	CANIDM4 |= (1<<IDEMSK);

	// enable reception and
	CANCDMOB=(1<<CONMOB1) | (1<<IDE);

	// wait until reception is complete
	while(!(CANSTMOB&(1<<RXOK)));

	// reset flag
	CANSTMOB &= ~(1<<RXOK);

	// get data
	for (i=0; i<(CANCDMOB&0xf); i++)
		//msg.data[i] = CANMSG;
		msg_tmp[i]=CANMSG;

	//get identifier which has to be the same like ID
	msg.id = 0;
	msg.id |= ((unsigned long) CANIDT1<<24);
	msg.id |= ((unsigned long) CANIDT2<<16);
	msg.id |= ((unsigned long) CANIDT3<<8);
	msg.id |= (CANIDT4&0xF8);
	msg.id >>= 3;
}
