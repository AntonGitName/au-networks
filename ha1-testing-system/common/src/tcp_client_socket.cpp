//
// Created by antonpp on 05.04.17.
//

#include "tcp_client_socket.h"

void tcp_client_socket::send(const void *buf, size_t size) {
    if (!server_socket) {
        server_socket->send(buf, size);
    } else {
        throw client_socket_exception("Cannot call `send` while not connected.");
    }
}

void tcp_client_socket::recv(void *buf, size_t size) {
    if (!server_socket) {
        server_socket->recv(buf, size);
    } else {
        throw client_socket_exception("Cannot call `recv` while not connected.");
    }
}

tcp_client_socket::~tcp_client_socket() {
    close(client_socket_fd);
}

void tcp_client_socket::connect() {
    auto server_address = util::create_socket_address(hostname, port);
    int server_socket_fd = ::connect(client_socket_fd, (sockaddr *) &server_address, sizeof(server_address));
    if (server_socket_fd < 0) {
        throw client_socket_exception("Failed to connect to the server.");
    }
    server_socket.reset(new tcp_accepted_socket(server_socket_fd));
}

tcp_client_socket::tcp_client_socket(const std::string &hostname, const int port) : hostname(hostname), port(port) {
    if ((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw client_socket_exception("Could not create socket");
    }
}
