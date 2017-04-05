#include <iostream>

#include "server.h"

namespace {
    const std::string DEFAULT_HOST = "127.0.0.1";
    const int DEFAULT_PORT = 40001;
}

void usage() {
    std::cout << "USAGE: "
            "         server [host [port]]";
}

int main(int argc, const char **argv) {

    std::string host = DEFAULT_HOST;
    int port = DEFAULT_PORT;


    if (argc > 1) {
        host = argv[1];
        if (argc == 3) {
            port = std::stoi(argv[2]);
        } else {
            usage();
            return 1;
        }
    }

    try {
        server server(host, port);

        std::cout << std::endl << "Type `stop` to stop the server." << std::endl;

        for (;;) {
            std::cout << "> ";
            std::string str;
//            std::cin >> str;
            std::getline(std::cin, str);
            if (str == "stop") {
                break;
            }
        }
    } catch (network_exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}