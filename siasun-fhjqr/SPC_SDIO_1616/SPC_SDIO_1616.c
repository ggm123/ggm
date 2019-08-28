/*
 * SPC_SDIO_1616.c
 *
 *  Created on: 2019-8-26
 *      Author: siasunggm
 */

#include <SPC_SDIO_1616.h>
#include <stdio.h>

 canBus_t *CAN0;

SPC_SDIO_1616_t SPC_SDIO_1616a_Analyze_Data()
{
    float import0, import1,import2,import3;
	SPC_SDIO_1616_t SPC_SDIO_1616a;
	import0 = (int)((short)(CAN0->recvBuffer.data[0]));
	import1 = (int)((short)(CAN0->recvBuffer.data[1]));
	import2 = (int)((short)(CAN0->recvBuffer.data[2]));
	import3 = (int)((short)(CAN0->recvBuffer.data[3]));
    SPC_SDIO_1616a.import0 = import0;
    SPC_SDIO_1616a.import1 = import1;
    SPC_SDIO_1616a.import2 = import2;
    SPC_SDIO_1616a.import3 = import3;
    printf("SPC_SDIO_1616a_import0=%d\n", import0);
    printf("SPC_SDIO_1616a_import1=%d\n", import1);
    printf("SPC_SDIO_1616a_import2=%d\n", import2);
    printf("SPC_SDIO_1616a_import3=%d\n", import3);
    return SPC_SDIO_1616a;
}
SPC_SDIO_1616_t SPC_SDIO_1616c_Analyze_Data()
{
			float import0, import1,import2,import3;
			SPC_SDIO_1616_t SPC_SDIO_1616c;
			import0 = (int)((short)(CAN0->recvBuffer.data[0] ) ) ;
			import1 = (int)((short)(CAN0->recvBuffer.data[1] ) ) ;
			import2 = (int)((short)(CAN0->recvBuffer.data[2] ) ) ;
			import3 = (int)((short)(CAN0->recvBuffer.data[3] ) ) ;
			SPC_SDIO_1616c.import0 = import0;
			SPC_SDIO_1616c.import1 = import1;
			SPC_SDIO_1616c.import2 = import2;
			SPC_SDIO_1616c.import3 = import3;
			printf("SPC_SDIO_1616c_import0=%d\n", import0);
			printf("SPC_SDIO_1616c_import1=%d\n", import1);
			printf("SPC_SDIO_1616c_import2=%d\n", import2);
			printf("SPC_SDIO_1616c_import3=%d\n", import3);
    	    return SPC_SDIO_1616c;
}



