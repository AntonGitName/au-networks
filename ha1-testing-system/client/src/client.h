//
// Created by antonpp on 05.04.17.
//

#pragma once


#include <memory>

#include "tcp_client_socket.h"
#include "protocol.h"

class client {
public:
    client(std::string hostname, int port);

    void start_test();

    void get_test_results();

    void next_question();

    void answer_question(int x);

private:

    std::unique_ptr<tcp_client_socket> client_socket;

    void send_msg(protocol::client_message *msg);
};
