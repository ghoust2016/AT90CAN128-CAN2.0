#ifndef CAN_H_INCLUDED
#define CAN_H_INCLUDED

#include "config.h"

void InitCAN(void);
void MOB_send(void);
//void can_init(void);
void can_tx(struct MOb msg);
void can_rx(struct MOb msg);

#endif // CAN_H_INCLUDED
