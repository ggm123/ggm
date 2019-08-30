//
// Created by siasunhebo on 19-8-29.
//

#ifndef IMUTEST_BUFFER_H
#define IMUTEST_BUFFER_H


#include <string.h>

#define BUFFER_SIZE 26

struct Buffer{
    int size;
    char data[BUFFER_SIZE];

};

void buffer_init(struct Buffer *buf)
{
    buf->size = 0;
}

int buffer_add(struct Buffer *buf, const char *tmp, int len)
{
    if (buf->size + len > BUFFER_SIZE)
    {
        return -1;
    }
    memcpy(buf->data + buf->size, tmp, len);
    buf->size += len;
    return len;
}

int buffer_del(struct Buffer *buf, int len)
{
    int size = buf->size - len;
    if (size < 0)
    {
        return -1;
    }
    memcpy(buf->data, buf->data + len, size);
    buf->size -= len;
    return len;
}

#endif //IMUTEST_BUFFER_H
