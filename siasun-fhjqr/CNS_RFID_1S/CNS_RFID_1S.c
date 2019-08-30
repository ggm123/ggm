/*
 * CNS_RFID_1S.C
 *
 *  Created on: 2019-8-27
 *      Author: siasunggm
 */

#include <CNS_RFID_1S.h>
#include <stdio.h>

 canBus_t *CAN0;

 CNS_RFID_1S_t CNS_RFID_1S_Analyze_Data()
{
    float import0, import1,import2,import3;
    CNS_RFID_1S_t CNS_RFID_1S;
    import0 = (int)((short)(CAN0->recvBuffer.data[0]));
    import1 = (int)((short)(CAN0->recvBuffer.data[1]));
    import2 = (int)((short)(CAN0->recvBuffer.data[2]));
    import3 = (int)((short)(CAN0->recvBuffer.data[3]));
    CNS_RFID_1S.import0 = import0;
    CNS_RFID_1S.import1 = import1;
    CNS_RFID_1S.import2 = import2;
    CNS_RFID_1S.import3 = import3;
    printf("CNS_RFID_1S_import0=%d\n", import0);
    printf("CNS_RFID_1S_import1=%d\n", import1);
    printf("CNS_RFID_1S_import2=%d\n", import2);
    printf("CNS_RFID_1S_import3=%d\n", import3);
    return CNS_RFID_1S;
}



