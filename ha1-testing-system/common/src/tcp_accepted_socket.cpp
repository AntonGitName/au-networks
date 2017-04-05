//
// Created by antonpp on 05.04.17.
//

#include "tcp_accepted_socket.h"

tcp_accepted_socket::tcp_accepted_socket(int socket_fd) : socket_fd(socket_fd) {}

tcp_accepted_socket::~tcp_accepted_socket() {
    close(socket_fd);
}

void tcp_accepted_socket::recv(void *buf, size_t size) {
    size_t read_bytes = 0;
    char *cbuf = (char *) buf;
    while (read_bytes < size) {
        auto rb = read(socket_fd, cbuf + read_bytes, size - read_bytes);
        if (rb <= 0) {
            throw connection_exception("IO error during reading");
        }

        read_bytes += rb;
    }
}

void tcp_accepted_socket::send(const void *buf, size_t size) {
    size_t written_bytes = 0;
    char *cbuf = (char *) buf;
    while (written_bytes < size) {
        auto wb = ::send(socket_fd, cbuf + written_bytes, size - written_bytes, MSG_NOSIGNAL);
        if (wb <= 0) {
            throw connection_exception("IO error during writing");
        }

        written_bytes += wb;
    }
}