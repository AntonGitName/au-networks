//
// Created by antonpp on 05.04.17.
//

#pragma once


#include <memory>

#include "tcp_client_socket.h"

class client {
public:
    client(std::string hostname, int port);

private:
    std::unique_ptr<tcp_client_socket> client_socket;
};
