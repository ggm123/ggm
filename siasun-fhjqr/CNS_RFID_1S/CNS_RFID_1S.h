/*
 * CNS_RFID_1S.h
 *
 *  Created on: 2019-8-27
 *      Author: siasunhebo
 */

#ifndef CNS_RFID_1S_H_
#define CNS_RFID_1S_H_

#include <can.h>

typedef struct CNS_RFID_1S
{
    int import0;
    int import1;
    int import2;
    int import3;
}CNS_RFID_1S_t;

CNS_RFID_1S_t CNS_RFID_1S_Analyze_Data();



#endif /* CNS_RFID_1S_H_ */
