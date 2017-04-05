//
// Created by antonpp on 05.04.17.
//

#include "tcp_server_socket.h"

namespace {
    const int MAX_REQUESTS = 8;
}

tcp_server_socket::tcp_server_socket(const std::string &host, int port) throw(server_socket_exception) {
    // yep, some plane C shit code
    auto proto = getprotobyname("TCP");
    // open
    socket_fd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
    if (socket_fd < 0) {
        throw server_socket_exception("Could not open socket");
    }
    // get address
    auto server_address = util::create_socket_address(host, port);
    // bind
    if (bind(socket_fd, (sockaddr *) &server_address, sizeof(server_address)) < 0) {
        throw server_socket_exception("Could not bind new socket to specified host/port");
    }

    listen(socket_fd, MAX_REQUESTS);
}

stream_socket *tcp_server_socket::accept_one_client() throw(server_socket_exception) {
    sockaddr_in client_address;
    socklen_t socklen = sizeof(client_address);
    int accepted_socket_fd = accept(socket_fd, (struct sockaddr *) &client_address, &socklen);
    if (accepted_socket_fd < 0) {
        throw server_socket_exception("Could not accept a connection.");
    }
    return new tcp_accepted_socket(accepted_socket_fd);
}

tcp_server_socket::~tcp_server_socket() {
    shutdown(socket_fd, SHUT_RDWR);
//    close(socket_fd);
}