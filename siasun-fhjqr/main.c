/*
 * main.c
 *
 *  Created on: Aug 24, 2019
 *      Author: siasunggm
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h>
#include <can.h>
#include <time.h>
#include <signal.h>
#include <Timer.h>
#include <zconf.h>
#include <CNS_MGS_160S.h>
#include <SPC_SDIO_1616.h>
#include <CNS_RFID_1S.h>
#include <FD123_CA_000.h>
#include <HC_SuK043_C.h>



extern canBus_t *CAN0;

extern int SDIOa_Out0,  SDIOa_Out1,  SDIOa_Out2,  SDIOa_Out3;
extern int SDIOc_Out0,  SDIOc_Out1,  SDIOc_Out2,  SDIOc_Out3;


CNS_MGS_160S_t POINT0,POINT1;

SPC_SDIO_1616_t IMPORT0,IMPORT1;
SPC_SDIO_1616_t OUPUT0,OUPUT1;

CNS_RFID_1S_t POINTa;
FD123_CA_000_t POINTb;
HC_SuK043_C_t POINTc;

void Prase_Sensor_Data()
{
	CanRecvThread(CAN0);  //CAN接收

	 if(CAN0->sendBuffer.can_id==0x03)
	 {
		 POINT0 = CNS_MGS_160Sa_Analyze_Data();  //解析磁条传感器0
	 }
	 else if(CAN0->sendBuffer.can_id==0x04)
	 {
		 POINT1 = CNS_MGS_160Sc_Analyze_Data();  //解析磁条传感器1
	 }
	 else if(CAN0->sendBuffer.can_id==0x05)//解析显示屏
	 {
         POINTc = HC_SuK043_C_Analyze_Data();
	 }
	 else if(CAN0->sendBuffer.can_id==0x06)//解析RFID
	 {
		 POINTa = CNS_RFID_1S_Analyze_Data();
	 }
     else if(CAN0->sendBuffer.can_id==0x07)//解析驱动器
     {
         POINTb = FD123_CA_000_Analyze_Data();
     }

	  if(CAN0->recvBuffer.can_id==0x08)//解析远程IO0
	 {
		 IMPORT0 = SPC_SDIO_1616a_Analyze_Data();
	 }
	 else if(CAN0->recvBuffer.can_id==0x09) //解析远程IO1
	 {
		 IMPORT1 = SPC_SDIO_1616c_Analyze_Data();
	 }
}

void SDIO_Out_Data()
{
	int SDIOa_Out0,  SDIOa_Out1,  SDIOa_Out2,  SDIOa_Out3;
    int SDIOc_Out0,  SDIOc_Out1,  SDIOc_Out2,  SDIOc_Out3;

	SDIOa_Out0 = (int)(0x00);
	SDIOa_Out1 = (int)(0x00);
	SDIOa_Out2 = (int)(0x00);
	SDIOa_Out3 = (int)(0x00);

	SDIOc_Out0 = (int)(0x00);
	SDIOc_Out1 = (int)(0x00);
	SDIOc_Out2 = (int)(0x00);
	SDIOc_Out3 = (int)(0x00);

	CanSendThread(CAN0);//CAN发送
}


int main ()
{
	CAN_init();      //CAN总线初始化

	while(1)
	{
		Prase_Sensor_Data();    //传感器处理
		SDIO_Out_Data();    //SDIO输出

	}

}
