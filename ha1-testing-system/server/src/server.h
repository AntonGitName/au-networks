//
// Created by antonpp on 05.04.17.
//

#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <thread>

#include "tcp_server_socket.h"

class server {
public:
    server(std::string hostname, int port);

    ~server();

private:
    void handle_connection(std::unique_ptr<stream_socket> client_socket);

    void print_to_console(const std::string &msg);

    std::shared_ptr<stream_server_socket> _socket;
    std::shared_ptr<std::thread> _listen_thread;
    bool running = true;

};
