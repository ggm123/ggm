//
// Created by siasunhebo on 19-8-29.
//

#ifndef IMUTEST_PROTOCOL_H
#define IMUTEST_PROTOCOL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

char* parse_packet(struct Buffer *buf);

char* parse_packet(struct Buffer *buf)
{
    if (buf->size == 0) {
        return NULL;
    }
    int head_len;
    int body_len;

    {
        char *body1;
        body1 = memchr(buf->data, '|', buf->size);//查找里面第一个和目标字符匹配的字符 ,参数：buf->data首地址  '|'想要查找的字符值   buf->size查到那个地址

        printf("body = %s\n", body1);
        if (body1 == NULL) {
            printf("[Partial Packet] header not ready, buffer %d\n", buf->size);
            return NULL;
        }
        body1++;
        head_len = body1 - buf->data;
    }

    {
        char header[20];
        memcpy(header, buf->data, head_len - 1);//它的功能是从buf->data的开始位置拷贝 head_len - 1个字节的数据到header
        header[head_len - 1] = '\0';
        body_len = 26;
    }


    char *body = malloc(body_len + 1);
    if (body_len > 0) {
        memcpy(body, buf->data, body_len);
    }
    body[body_len] = '\0';

    buffer_del(buf, body_len);
    return body;
}

#endif //IMUTEST_PROTOCOL_H
