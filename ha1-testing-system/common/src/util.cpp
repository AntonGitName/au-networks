//
// Created by antonpp on 05.04.17.
//

#include "util.h"

namespace util {
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
}