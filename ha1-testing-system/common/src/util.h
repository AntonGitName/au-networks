//
// Created by antonpp on 05.04.17.
//

#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netdb.h>
#include <string>

#include "network_exception.h"

namespace util {
    const std::string DEFAULT_HOST = "127.0.0.1";
    const int DEFAULT_PORT = 40001;

    sockaddr_in create_socket_address(const std::string &hostname, int port) throw(network_exception);
}
