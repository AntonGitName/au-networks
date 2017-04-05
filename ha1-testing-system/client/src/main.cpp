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

    try {
        client client(host, port);

        std::cout << std::endl << "Type `help` to see list of commands." << std::endl;

        for (;;) {
            std::cout << "> ";
            std::string str;
//            std::cin >> str;
            std::getline(std::cin, str);
            if (str == "start") {
                client.start_test();
            } else if (str == "next") {
                client.next_question();
            } else if (str == "results") {
                client.get_test_results();
            } else if (str == "answer") {
//                client.get_test_results();
            } else {

            }
        }
    } catch (network_exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}