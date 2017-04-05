//
// Created by antonpp on 05.04.17.
//
#include <iostream>

#include "util.h"
#include "client.h"

void usage(const std::string &bin_name) {
    std::cout << "USAGE: \n"
                         "         " + bin_name + " [host [port]]";
}

int main(int argc, const char **argv) {

    std::string host = util::DEFAULT_HOST;
    int port = util::DEFAULT_PORT;


    if (argc > 1) {
        host = argv[1];
        if (argc == 3) {
            port = std::stoi(argv[2]);
        } else {
            usage(argv[0]);
            return 1;
        }
    }
    client client(host, port);
    return 0;
}