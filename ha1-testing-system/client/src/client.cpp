//
// Created by antonpp on 05.04.17.
//

#include "client.h"

using namespace protocol;

client::client(std::string hostname, int port) : client_socket(new tcp_client_socket(hostname, port)) {
    client_socket->connect();
}

void client::start_test() {
    start_message msg;
    send_msg(&msg);
}

void client::answer_question(int x) {
    check_message msg(x);
    send_msg(&msg);
}

void client::next_question() {
    next_message msg;
    send_msg(&msg);
}

void client::get_test_results() {
    send_message msg;
    send_msg(&msg);

}

void client::send_msg(client_message *msg) {
    protocol::send(msg->serialize(), client_socket.get());
}
