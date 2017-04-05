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
    // set host
    sockaddr_in server_address;
    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    if (inet_pton(AF_INET, host.c_str(), &server_address.sin_addr) <= 0) {
        char ip[32];
        if (auto he = gethostbyname(host.c_str())) {
            auto addr_list = he->h_addr_list;

            strcpy(ip, addr_list[0]);
            if (addr_list[1]) {
                throw server_socket_exception("Provided more then one host names");
            }
        } else {
            throw server_socket_exception("Couldn't resolve hostname");
        }
        if (inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0) {
            throw server_socket_exception("Failed to set specified hostname");
        }
    }
    // set port
    server_address.sin_port = htons((uint16_t) port);
    // bind
    if (bind(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
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