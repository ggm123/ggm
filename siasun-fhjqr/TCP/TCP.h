//
// Created by siasunhebo on 19-8-29.
//

#ifndef IMUTEST_TCP_H
#define IMUTEST_TCP_H




void Get_TCP_Init();   //初始化接收电台数据
void Get_Transceiver_Data();  //接收电台数据
void Get_Pthread();
void *Data_Tcp(void *t);
int Transceiver_Send(char buf[]);

#endif //IMUTEST_TCP_H
