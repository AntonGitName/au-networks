//
// Created by antonpp on 05.04.17.
//

#pragma once


#include <memory>

#include "tcp_client_socket.h"
#include "protocol.h"

struct client_exception : network_exception {
    client_exception(const std::string &msg) : network_exception("Client task failed. Cause: " + msg) {}
};

class client {
public:
    client(std::string hostname, int port);

    void start_test() throw(client_exception);

    std::vector<protocol::question_verdict> get_test_results() throw(client_exception);

    std::string next_question() throw(client_exception);

    void answer_question(int x) throw(client_exception);

    bool is_test_started() const;

private:

    bool test_started = false;

    std::unique_ptr<tcp_client_socket> client_socket;

    void send_msg(protocol::client_message *msg) throw(client_exception);

    std::shared_ptr<protocol::server_message> receive_msg() throw(client_exception);
};
