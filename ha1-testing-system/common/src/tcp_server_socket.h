//
// Created by antonpp on 05.04.17.
//

#pragma once


#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory.h>

#include "stream_socket.h"
#include "network_exception.h"
#include "tcp_accepted_socket.h"

struct server_socket_exception : network_exception {
    server_socket_exception(const std::string &msg) : network_exception(msg) {}
};

class tcp_server_socket : public stream_server_socket {
public:
    tcp_server_socket(const std::string &host, int port) throw(server_socket_exception);

    ~tcp_server_socket();

    stream_socket *accept_one_client() throw(server_socket_exception);

private:
    int socket_fd;
};
