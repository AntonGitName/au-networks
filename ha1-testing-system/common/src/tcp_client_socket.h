//
// Created by antonpp on 05.04.17.
//

#pragma once

#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <memory.h>
#include <memory>

#include "util.h"
#include "stream_socket.h"
#include "network_exception.h"
#include "tcp_accepted_socket.h"

struct client_socket_exception : network_exception {
    client_socket_exception(const std::string &msg) : network_exception(msg) {}
};

class tcp_client_socket : public stream_client_socket {
public:
    tcp_client_socket(const std::string &hostname, const int port);

    void send(const void *buf, size_t size) override;

    void recv(void *buf, size_t size) override;

    void connect() override;

private:
    std::unique_ptr<tcp_accepted_socket> client_socket;

    const std::string &hostname;
    const int port;
    int client_socket_fd;
};
