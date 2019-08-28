/*
 * can.c
 *
 *  Created on: Aug 24, 2019
 *      Author: siasunggm
 */


#include <can.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <linux/socket.h>
#include <linux/can.h>
#include <linux/can/error.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

#define errout(_s)	fprintf(stderr, "error class: %s\n", (_s))
#define errcode(_d) fprintf(stderr, "error code: %02x\n", (_d))

canBus_t *CAN0;

int  SDIOa_Out0, SDIOa_Out1, SDIOa_Out2, SDIOa_Out3;
int  SDIOc_Out0, SDIOc_Out1, SDIOc_Out2, SDIOc_Out3;


void CAN_init()
{
	CAN0 = CanBusInit("can0");       //init can
}

static void handle_err_frame(const struct can_frame *fr)
{
	if (fr->can_id & CAN_ERR_TX_TIMEOUT)
	{
		errout("CAN_ERR_TX_TIMEOUT");
		printf("发送超时");
	}
	if (fr->can_id & CAN_ERR_LOSTARB)
	{
		errout("CAN_ERR_LOSTARB");
        printf("总线仲裁错误");
		errcode(fr->data[0]);
	}
	if (fr->can_id & CAN_ERR_CRTL)
	{
        if(fr->data && fr->can_dlc >= 2)
        {
            switch(fr->data[1])
            {
                case CAN_ERR_CRTL_RX_OVERFLOW:  printf("接收缓存溢出");    break;
                case CAN_ERR_CRTL_TX_OVERFLOW:  printf("发送缓存溢出");    break;
                case CAN_ERR_CRTL_RX_WARNING:   printf("接收报警");        break;
                case CAN_ERR_CRTL_TX_WARNING:   printf("发送报警");        break;
                case CAN_ERR_CRTL_RX_PASSIVE:   printf("接收被动错误");    break;
                case CAN_ERR_CRTL_TX_PASSIVE:   printf("发送被动错误");    break;
            }
            errout("CAN_ERR_CRTL");
            errcode(fr->data[1]);
        }
        else
            errout("CAN_ERR_CRTL");
            printf("CAN控制器错误");
		    errcode(fr->data[1]);
	}
	if (fr->can_id & CAN_ERR_PROT)
	{
	    if(fr->data && fr->can_dlc >= 4)
        {
            switch(fr->data[2])
            {
                case CAN_ERR_PROT_BIT:      printf("位错误");           break;
                case CAN_ERR_PROT_FORM:     printf("帧格式错误");       break;
                case CAN_ERR_PROT_STUFF:    printf("位填充错误");       break;
                case CAN_ERR_PROT_BIT0:     printf("(接收站)不能发送占有位(dominant bit)"); break;
                case CAN_ERR_PROT_BIT1:     printf("(发送站)不能发送空闲位(recessive bit)"); break;
                case CAN_ERR_PROT_OVERLOAD: printf("总线超负荷");       break;
                case CAN_ERR_PROT_ACTIVE:   printf("主动错误");         break;
                case CAN_ERR_PROT_TX:       printf("传输错误");         break;
            }
            errout("CAN_ERR_CRTL");
            errcode(fr->data[2]);
        }
	    else
        {
	        printf("协议违反");
            errout("CAN_ERR_PROT");
            errcode(fr->data[3]);
        }
	}
	if (fr->can_id & CAN_ERR_TRX)
	{
		errout("CAN_ERR_TRX");
		errcode(fr->data[4]);
	}
	if (fr->can_id & CAN_ERR_ACK)
	{
        printf("应答错误");
		errout("CAN_ERR_ACK");
	}
	if (fr->can_id & CAN_ERR_BUSOFF)
	{
        printf("总线关闭");
		errout("CAN_ERR_BUSOFF");
	}
	if (fr->can_id & CAN_ERR_BUSERROR)
	{
        printf("总线错误(可能溢出)");
		errout("CAN_ERR_BUSERROR");
	}
	if (fr->can_id & CAN_ERR_RESTARTED)
	{
        printf("CAN控制器重启");
		errout("CAN_ERR_RESTARTED");
	}
}
#define myerr(str)	fprintf(stderr, "%s, %s, %d: %s\n", __FILE__, __func__, __LINE__, str)


void print_frame(struct can_frame *fr)
{
	int i;
	printf("%08x\n", fr->can_id & CAN_EFF_MASK);
	//printf("%08x\n", fr->can_id);
	printf("dlc = %d\n", fr->can_dlc);
	printf("data = ");
	for (i = 0; i < fr->can_dlc; i++)
		printf("%02x ", fr->data[i]);
	printf("\n");
}

/*
canbus初始化函数
char *interface：can设备接口名
canBus_t * ：返回的canbus结构体
*/
canBus_t  *CanBusInit(char *interface)
{
    canBus_t *canbus_ptr = (canBus_t *)malloc(sizeof(canBus_t));
    memset(canbus_ptr, 0, sizeof(canBus_t));
    pthread_mutex_init(&canbus_ptr->rdwrLock, NULL);
    struct sockaddr_can addr;
    struct ifreq ifr;
    if((canbus_ptr->canFd = socket(PF_CAN,SOCK_RAW,CAN_RAW))<0) //创建 SocketCAN 套接字
    {
        printf("socket err!\n");
    }
    strcpy(ifr.ifr_name,interface);
    if(-1 == (ioctl(canbus_ptr->canFd,SIOCGIFINDEX,&ifr))) //指定 can0 设备
    {
        printf("ioctl err!\n");
    }

	strncpy(ifr.ifr_name, interface, IFNAMSIZ - 1); //将接口传递给ifr
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';
	ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name); //检查接口是否真的存在
	if (!ifr.ifr_ifindex)
	{
		perror("if_nametoindex");
		return 0;
	}
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if((bind(canbus_ptr->canFd,(struct sockaddr*)&addr,sizeof(addr))) < 0) //将套接字与 can0 绑定
    {
        printf("bind err!\n");
    }

    return canbus_ptr;
}

/*
can设备发送线程
*/

void CanSendThread(canBus_t *can)
{
	int ret;
if(can->sendBuffer.can_id==0x03)//轮循读磁条传感器1
	{
		can->sendBuffer.can_id = 0x04;
		can->sendBuffer.can_dlc = 02;
		can->sendBuffer.data[0] = 0x88;
		can->sendBuffer.data[1] = 0x00;
	}
else if(can->sendBuffer.can_id==0x04)
{
	can->sendBuffer.can_id = 0x05;
	can->sendBuffer.can_dlc = 2;
	can->sendBuffer.data[0] = 0x4D;
	can->sendBuffer.data[1] = 0x04;
}
else if(can->sendBuffer.can_id==0x05)//轮循RFID传感器
{
	can->sendBuffer.can_id = 0x06;
	can->sendBuffer.can_dlc = 4;
	can->sendBuffer.data[0] = 0x4D;
	can->sendBuffer.data[1] = 0x04;
}
else if(can->sendBuffer.can_id==0x06)
{
	can->sendBuffer.can_id = 0x07;
	can->sendBuffer.can_dlc = 2;
	can->sendBuffer.data[0] = 0x00;
	can->sendBuffer.data[1] = 0x00;
}
else if(can->sendBuffer.can_id==0x07)
{
	can->sendBuffer.can_id = 0x208;
	can->sendBuffer.can_dlc = 04;
	can->sendBuffer.data[0] = SDIOa_Out0;
	can->sendBuffer.data[1] = SDIOa_Out1;
	can->sendBuffer.data[2] = SDIOa_Out2;
	can->sendBuffer.data[3] = SDIOa_Out3;
}
else if(can->sendBuffer.can_id==0x208)
{
	can->sendBuffer.can_id = 0x209;
	can->sendBuffer.can_dlc = 04;
	can->sendBuffer.data[0] = SDIOc_Out0;
	can->sendBuffer.data[1] = SDIOc_Out1;
	can->sendBuffer.data[2] = SDIOc_Out2;
	can->sendBuffer.data[3] = SDIOc_Out3;
}

else//轮循读磁条传感器0
{
	can->sendBuffer.can_id = 0x03;
	can->sendBuffer.can_dlc = 02;
	can->sendBuffer.data[0] = 0x88;
	can->sendBuffer.data[1] = 0x00;
}
	ret = write(can->canFd, &can->sendBuffer, sizeof(struct can_frame));
    if(ret  != sizeof(can->sendBuffer))
    {
        printf("Send Error can->sendBuffer\n!");//发送错误
    }
	else
	    printf("send thread done!\n");

}


void CanRecvThread(canBus_t *can)
{
	int nbytes;
	int ret;
	struct timeval tv;
	fd_set rset;

	FD_ZERO(&rset);
	FD_SET(can->canFd, &rset);

	printf("this is can select\n");
	ret = select(can->canFd + 1, &rset, NULL, NULL, NULL);
	if (ret == 0)
	{
		myerr("select time out");
		return;
	}

	nbytes = read(can->canFd, &can->recvBuffer, sizeof(struct can_frame));
    printf("this is can read\n");
	if (can->recvBuffer.can_id & CAN_ERR_FLAG)             /* 出错设备错误 */
	{
		handle_err_frame(&can->recvBuffer);
		myerr("CAN device error");
		return;
	}
}



int CanBusTestMode()
{
	//timerThread = TimerRoutineInit();   //初始化timer线程
	canBus_t *CAN0 = CanBusInit("can0");       //init can
	pthread_t canRecvCan0, canSendCan0;              //can0接收线程句柄
    pthread_create(&canRecvCan0, NULL, (void *)CanRecvThread, CAN0);

    //create a job

	TaskAdd_t MASTER_CTRL_ESA_Task;  //创建任务名
    //MASTER_CTRL_ESA_Task.task = CanSendThread;   //任务为发送线程
    MASTER_CTRL_ESA_Task.arg.boId = 0x100;
    MASTER_CTRL_ESA_Task.arg.can = CAN0;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.can_dlc = 8;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.can_id = 0x300;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[0] = 1;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[1] = 2;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[2] = 3;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[3] = 4;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[4] = 5;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[5] = 6;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[6] = 7;
    MASTER_CTRL_ESA_Task.arg.can->sendBuffer.data[7] = 8;

    pthread_create(&canSendCan0, NULL, (void *)CanSendThread, &MASTER_CTRL_ESA_Task);

}
