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

void help() {
    std::cout << "\nHelp: \n"
            " start     = start new test\n"
            " next      = request next question\n"
            " answer N  = send answer for the last question\n"
            " result    = show current results\n"
            " exit      = quit application";
}

std::string verdict_to_str(protocol::question_verdict v) {
    switch (v) {
        case protocol::CORRECT:
            return "+";
        case protocol::WRONG:
            return "-";
        default:
            return "?";
    }
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

        std::cout << std::endl << "Type `help` to see list of available commands." << std::endl;

        for (;;) {
//            std::cout << "> ";
            std::string str;
            std::cin >> str;
//            std::getline(std::cin, str);
            if (str == "start") {
                client.start_test();
            } else if (str == "next") {
                if (client.is_test_started()) {
                    std::cout << std::endl << client.next_question() << std::endl;
                } else {
                    std::cout << "You have to start test first.\n";
                }
            } else if (str == "results") {
                if (client.is_test_started()) {
                    auto r = client.get_test_results();
                    for (int i = 0; i < r.size(); ++i) {
                        std::cout << i + 1 << " " << verdict_to_str(r[i]) << std::endl;
                    }
                } else {
                    std::cout << "You have to start test first.\n";
                }

            } else if (str == "answer") {
                std::cin >> str;
                client.answer_question(std::atoi(str.c_str()));
            } else if (str == "exit") {
                break;
            } else {
                help();
            }
        }
    } catch (network_exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}