//
// Created by antonpp on 05.04.17.
//

#pragma once

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>


#include "stream_socket.h"
#include "network_exception.h"

struct connection_exception : network_exception {
    connection_exception(const std::string &msg) : network_exception(msg) {}
};

class tcp_accepted_socket : public stream_socket {
public:
    tcp_accepted_socket(int socket_fd);

    ~tcp_accepted_socket();

    void send(const void *buf, size_t size) override;

    void recv(void *buf, size_t size) override;

private:
    const int socket_fd;
};