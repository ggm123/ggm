/*
 * HC_SuK043_C.c
 *
 *  Created on: 2019-8-27
 *      Author: siasunggm
 */

#include <HC_SuK043_C.h>
#include <stdio.h>

canBus_t *CAN0;

HC_SuK043_C_t HC_SuK043_C_Analyze_Data()
{
    float import0, import1,import2,import3;
    HC_SuK043_C_t HC_SuK043_C;
    import0 = (int)((short)(CAN0->recvBuffer.data[0]));
    import1 = (int)((short)(CAN0->recvBuffer.data[1]));
    import2 = (int)((short)(CAN0->recvBuffer.data[2]));
    import3 = (int)((short)(CAN0->recvBuffer.data[3]));
    HC_SuK043_C.import0 = import0;
    HC_SuK043_C.import1 = import1;
    HC_SuK043_C.import2 = import2;
    HC_SuK043_C.import3 = import3;
    printf("HC_SuK043_C_import0=%d\n", import0);
    printf("HC_SuK043_C_import1=%d\n", import1);
    printf("HC_SuK043_C_import2=%d\n", import2);
    printf("HC_SuK043_C_import3=%d\n", import3);
    return HC_SuK043_C;
}


