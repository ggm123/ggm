/*
 * CNS_MGS_160S.c
 *
 *  Created on: 2019-8-26
 *      Author: siasunggm
 */

#include <CNS_MGS_160S.h>
#include <stdio.h>

 canBus_t *CAN0;

CNS_MGS_160S_t CNS_MGS_160Sa_Analyze_Data()
{
    float point0, point1,point2;
    CNS_MGS_160S_t CNS_MGS_160Sa;
    point0 = (int)((short)(CAN0->recvBuffer.data[0]));
    point1 = (int)((short)(CAN0->recvBuffer.data[1]));
    point2 = (int)((short)(CAN0->recvBuffer.data[2]));
    CNS_MGS_160Sa.point0 = point0;
    CNS_MGS_160Sa.point1 = point1;
    CNS_MGS_160Sa.point2 = point2;
    printf("CNS_MGS_160Sa_point0=%d\n", point0);
    printf("CNS_MGS_160Sa_point1=%d\n", point1);
    printf("CNS_MGS_160Sa_point2=%d\n", point2);
    return CNS_MGS_160Sa;
}
CNS_MGS_160S_t CNS_MGS_160Sc_Analyze_Data()
{
    float point0, point1,point2;
    CNS_MGS_160S_t  CNS_MGS_160Sc;
    point0 = (int)((short)(CAN0->recvBuffer.data[0]));
    point1 = (int)((short)(CAN0->recvBuffer.data[1]));
    point2 = (int)((short)(CAN0->recvBuffer.data[2]));
    CNS_MGS_160Sc.point0= point0;
    CNS_MGS_160Sc.point1 = point1;
    CNS_MGS_160Sc.point2 = point2;
    printf("CNS_MGS_160b_point0=%d\n", point0);
    printf("CNS_MGS_160b_point1=%d\n", point1);
    printf("CNS_MGS_160b_point2=%d\n", point2);
    return CNS_MGS_160Sc;
}



