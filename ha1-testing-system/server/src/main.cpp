#include <iostream>

#include "server.h"


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