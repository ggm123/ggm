//
// Created by siasunhebo on 19-8-29.
//


#include <TCP.h>
#include <stdio.h>
#include <pthread.h>
#include <net.h>
#include <buffer.h>
#include <protocol.h>
#include <errno.h>
#include <unistd.h>



struct Buffer buf;

extern char buffer[8];  //发送电台数组
int sock;

typedef union
{
    short fdata;
    char ldata[2];
}Transceiver_Data;    //电台数据联合体



Transceiver_Data Data0;
Transceiver_Data Data1;
Transceiver_Data Data2;
Transceiver_Data Data3;
Transceiver_Data Data4;


void Get_TCP_Init()
{
    sock = sock_connect("192.168.1.10", 5000);
    if (sock == -1)
    {
        printf("error: %s\n", strerror(errno));
        exit(0);
        //return NULL;
    }
    printf("connnect 192.168.1.10:5000\n");

}

void Get_Pthread()
{
    int rc;
    long t;
    pthread_t tid;
    rc = pthread_create(&tid, NULL, Data_Tcp, (void *)t);//创建线程
    if (rc)
    {
        printf("pthread create failed!\n");
        return;
    }
}


void *Data_Tcp(void *t)
{

    buffer_init(&buf);

    while (1)
    {
        Transceiver_Send(buffer);     //套接字发送(放主函数会有接收延迟) 电台数据发送
        char tmp[26];
        int len = read(sock, tmp, sizeof(tmp));    //套接字接收,网络套接字是IP地址与端口的组合.从指定的打开的文件sock中读取指定大小tmp从tmp开始的缓冲区
        printf("1200 REV LEN=%d\n", len);
        if (len <= 0)
        {
            printf("received %d, exit.\n", len);
            exit(0);
        }
        if (buffer_add(&buf, tmp, len) == -1)
        {
            printf("error, too large packet\n");
            exit(0);
        }
        int n = 0;
        while (1)
        {
            char *msg = parse_packet(&buf);
            if (!msg)
            {
                break;
            }
            n ++;
            printf("< %s\n", msg);
            if (n > 1)
            {
                printf(" [Mergerd Packed]\n");
            }
            free(msg);
        }
    }
    return 0;


}

int Transceiver_Send(char buf[])
{
    int num;
    if((num = send(sock, buf, 8, 0)) == -1)
    {
        printf("ERROR: Failed to sent string.\n");
        close(sock);
        exit(1);
    }
    //printf("OK: Sent %d bytes sucessful, please enter again.\n", num);
}

void Get_Transceiver_Data()
{
    Data0.ldata[0] = buf.data[4];
    Data0.ldata[1] = buf.data[5];

    Data0.ldata[0] = buf.data[8];
    Data0.ldata[1] = buf.data[9];

    Data1.ldata[0] = buf.data[18];
    Data1.ldata[1] = buf.data[19];

    Data2.ldata[0] = buf.data[20];
    Data2.ldata[1] = buf.data[21];

    Data3.ldata[0] = buf.data[22];
    Data3.ldata[1] = buf.data[23];

    Data4.ldata[0] = buf.data[24];
    Data4.ldata[1] = buf.data[25];
}
