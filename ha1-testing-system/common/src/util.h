//
// Created by antonpp on 05.04.17.
//

#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <netdb.h>
#include <string>
#include <vector>

#include "serializable.h"
#include "network_exception.h"

namespace util {

    const std::string DEFAULT_HOST = "127.0.0.1";

    const int DEFAULT_PORT = 40001;

    sockaddr_in create_socket_address(const std::string &hostname, int port) throw(network_exception);

    void append_int_to_bytes(std::vector<char> &v, int data);

    void append_string_to_bytes(std::vector<char> &v, const std::string &data);

    int read_int_from_bytes(const char *bytes, size_t length) throw(serialization_exception);

    std::vector<char> int_to_bytes(int x);

    int bytes_to_int(const char *x);

    std::string read_string_from_bytes(const char *bytes, size_t buffer, size_t length)  throw(serialization_exception);
}
