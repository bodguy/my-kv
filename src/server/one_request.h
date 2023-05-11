#ifndef MY_KV_ONE_REQUESRT_H
#define MY_KV_ONE_REQUESRT_H

#include <cstddef>
#include <cstdint>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory>
#include "io_helpers.h"

const size_t k_max_msg = 4096;

static int32_t one_request(int connfd) {
    // 4 bytes header
    char rbuf[4 + k_max_msg + 1];
    int32_t err = read_full(connfd, rbuf, 4);
    errno = 0;
    if (err) {
        if (errno == 0) {
            msg("EOF");
        } else {
            msg("read() error");
        }
        return err;
    }

    uint32_t len = 0;
    memcpy(&len, rbuf, 4); // assume little endian
    if (len > k_max_msg) {
        msg("too long");
        return -1;
    }

    // request body
    err = read_full(connfd, &rbuf[4], len);
    if (err) {
        msg("read() error");
        return err;
    }

    rbuf[4 + len] = '\0';
    spdlog::info("client says: {}", &rbuf[4]);

    // reply with the same protocol
    const char reply[] = "world";
    char wbuf[4 + sizeof(reply)];
    len = (uint32_t)strlen(reply);
    memcpy(wbuf, &len, 4);
    memcpy(&wbuf[4], reply, len);
    return write_all(connfd, wbuf, 4 + len);
}

#endif //MY_KV_ONE_REQUESRT_H
