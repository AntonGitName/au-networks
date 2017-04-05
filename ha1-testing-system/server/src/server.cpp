//
// Created by antonpp on 05.04.17.
//

#include <src/protocol.h>
#include "server.h"

server::server(std::string hostname, int port) {
    _socket = std::make_shared<tcp_server_socket>(hostname, port);
    _listen_thread = std::make_shared<std::thread>([this] {
        while (running) {
            try {
                auto client_socket = _socket->accept_one_client();
                handle_connection(std::unique_ptr<stream_socket>(client_socket));
            } catch (network_exception &e) {
                if (!running) {
                    print_to_console("Server was stopped by user.");
                } else {
                    print_to_console(std::string("Stopping server. Error occurred: ") + e.what());
                }
            }
        }
    });
    print_to_console("Server started.");
    print_to_console("Listening to port: " + std::to_string(port));
}

server::~server() {
    running = false;
    _socket.reset();
    // Not sure how to shutdown thread properly. This approach can hang an application
    // if closing socket does not wake up blocked on `accept` method thread for some reason.
    _listen_thread->join();
    print_to_console("Server was shut down successfully.");
}

void server::handle_connection(std::unique_ptr<stream_socket> client_socket) {
    print_to_console("Received new connection.");
    try {
        while (true) {
            auto data = protocol::receive(client_socket.get());
            print_to_console("Received msg");
        }
    } catch (network_exception &e) {
        print_to_console(e.what());
        print_to_console("Connection lost.");
    }
}

void server::print_to_console(const std::string &msg) {
    std::cout << std::endl << "[LOG] " << msg;

}
