//
// Created by antonpp on 05.04.17.
//

#include "tcp_client_socket.h"

void tcp_client_socket::send(const void *buf, size_t size) {
    if (client_socket) {
        client_socket->send(buf, size);
    } else {
        throw client_socket_exception("Cannot call `send` while not connected.");
    }
}

void tcp_client_socket::recv(void *buf, size_t size) {
    if (client_socket) {
        client_socket->recv(buf, size);
    } else {
        throw client_socket_exception("Cannot call `recv` while not connected.");
    }
}

void tcp_client_socket::connect() {
    auto server_address = util::create_socket_address(hostname, port);
    if (::connect(client_socket_fd, (sockaddr *) &server_address, sizeof(server_address)) < 0) {
        throw client_socket_exception("Connection to the server failed.");
    }
}

tcp_client_socket::tcp_client_socket(const std::string &hostname, const int port) : hostname(hostname), port(port) {
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd < 0) {
        throw client_socket_exception("Could not create socket");
    } else {
        client_socket.reset(new tcp_accepted_socket(client_socket_fd));
    }
}
