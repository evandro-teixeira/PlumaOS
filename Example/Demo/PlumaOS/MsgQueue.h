/*
 * MsgQueue.h
 *
 *  Created on: 27/12/2021
 *      Author: Evandro Teixeira
 */

#ifndef PLUMAOS_MSGQUEUE_H_
#define PLUMAOS_MSGQUEUE_H_


#include "PlumaOS_Types.h"


PlumaOS_Sts_t MsgQueue_Create(PlumaOS_Handle_t msgHandle, uint32_t msgNo, uint32_t msgSize);
PlumaOS_Sts_t MsgQueue_Put(PlumaOS_Handle_t msgHandle, void *pMessage);
PlumaOS_Sts_t MsgQueue_Get(PlumaOS_Handle_t msgHandle, void *pMessage);
uint16_t MsgQueue_AvailableMsgs(PlumaOS_Handle_t msgHandle);
PlumaOS_Sts_t MsgQueue_Destroy(PlumaOS_Handle_t msgHandle);

#endif /* PLUMAOS_MSGQUEUE_H_ */
