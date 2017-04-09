//
// Created by antonpp on 05.04.17.
//

#include "client.h"

using namespace protocol;

client::client(std::string hostname, int port) : client_socket(new tcp_client_socket(hostname, port)) {
    client_socket->connect();
}

void client::start_test() throw(client_exception) {
    start_message msg;
    send_msg(&msg);
    test_started = true;
}

void client::answer_question(int x) throw(client_exception) {
    check_message msg(x);
    send_msg(&msg);
}

std::string client::next_question()  throw(client_exception) {
    next_message msg;
    send_msg(&msg);
    auto response = receive_msg();
    if (auto r = std::dynamic_pointer_cast<protocol::question_message>(response)) {
        return r->get_text();
    } else {
        throw client_exception("unexpected server response");
    }
}

std::vector<question_verdict> client::get_test_results() throw(client_exception) {
    send_message msg;
    send_msg(&msg);
    auto response = receive_msg();
    if (auto r = std::dynamic_pointer_cast<protocol::results_message>(response)) {
        return r->get_verdicts();
    } else {
        throw client_exception("unexpected server response");
    }
}

std::shared_ptr<server_message> client::receive_msg() throw(client_exception) {
    try {
        auto data = protocol::receive(client_socket.get());
        auto ptr = server_message::deserialize(data);
        return ptr;
    } catch (network_exception &e) {
        throw client_exception(e.what());
    }
}

void client::send_msg(client_message *msg) throw(client_exception) {
    try {
        protocol::send(msg->serialize(), client_socket.get());
    } catch (network_exception &e) {
        throw client_exception(e.what());
    }
}

bool client::is_test_started() const {
    return test_started;
}