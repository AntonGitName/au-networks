//
// Created by antonpp on 05.04.17.
//

#include "util.h"

namespace util {

    namespace {
        union int_or_bytes {
            int x;
            char b[4];
        };
    }

    sockaddr_in create_socket_address(const std::string &hostname, int port) throw(network_exception) {
        // set host
        sockaddr_in socket_address;
        memset(&socket_address, '0', sizeof(socket_address));
        socket_address.sin_family = AF_INET;
        if (inet_pton(AF_INET, hostname.c_str(), &socket_address.sin_addr) <= 0) {
            char ip[32];
            if (auto he = gethostbyname(hostname.c_str())) {
                auto addr_list = he->h_addr_list;

                strcpy(ip, addr_list[0]);
                if (addr_list[1]) {
                    throw network_exception("Provided more then one host names");
                }
            } else {
                throw network_exception("Couldn't resolve hostname");
            }
            if (inet_pton(AF_INET, ip, &socket_address.sin_addr) <= 0) {
                throw network_exception("Failed to set specified hostname");
            }
        }
        // set port
        socket_address.sin_port = htons((uint16_t) port);

        return socket_address;
    }

    void append_int_to_bytes(std::vector<char> &v, int data) {
        int_or_bytes tmp;
        tmp.x = data;
        for (int i = 0; i < 4; ++i) {
            v.push_back(tmp.b[i]);
        }
    }

    void append_string_to_bytes(std::vector<char> &v, const std::string &data) {
        append_int_to_bytes(v, data.length());
        for (char c : data) {
            v.push_back(c);
        }
    }

    int read_int_from_bytes(const char *bytes, size_t length) throw(serialization_exception) {
        if (length != 4) {
            throw serialization_exception("Int size must be exactly 4 bytes");
        }
        int_or_bytes tmp;
        for (int i = 0; i < 4; ++i) {
            tmp.b[i] = bytes[i];
        }
        return tmp.x;
    }

    std::string
    read_string_from_bytes(const char *bytes, size_t buffer, size_t length)  throw(serialization_exception) {
        if (buffer < length) {
            throw serialization_exception("Not enough bytes for string");
        }
        return std::string(bytes, bytes + length);
    }
}