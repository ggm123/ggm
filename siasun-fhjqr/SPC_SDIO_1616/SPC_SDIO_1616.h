/*
 * SPC_SDIO_1616.h
 *
 *  Created on: 2019-8-26
 *      Author: siasunggm
 */

#ifndef SPC_SDIO_1616_H_
#define SPC_SDIO_1616_H_

#include <can.h>

typedef struct SPC_SDIO_1616
{
    int import0;
    int import1;
    int import2;
    int import3;
}SPC_SDIO_1616_t;

SPC_SDIO_1616_t SPC_SDIO_1616a_Analyze_Data();
SPC_SDIO_1616_t SPC_SDIO_1616c_Analyze_Data();
void SDIO_Out_Data();

#endif /* SPC_SDIO_1616_H_ */
