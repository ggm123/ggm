//
// Created by siasunhebo on 19-8-29.
//

#ifndef IMUTEST_NET_H
#define IMUTEST_NET_H

#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int sock_connect(const char *ip, int port);

int sock_connect(const char *ip, int port)
{
    int sock;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));//作用：bzero函数的作用是将addr指针指向的地址全部清零。
    addr.sin_family = AF_INET;//使用IPV4协议
    addr.sin_port = htons((short)port);//设置端口号
    inet_pton(AF_INET, ip, &addr.sin_addr);//设置IP地址

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        goto sock_err;
    }
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        goto sock_err;
    }
    return sock;

    sock_err:
    if (sock)
    {
        close(sock);
    }
    return -1;
}

#endif //IMUTEST_NET_H
