//
// Created by antonpp on 05.04.17.
//


#include "server.h"

using namespace protocol;

server::server(std::string hostname, int port) {
    _socket = std::make_shared<tcp_server_socket>(hostname, port);
    _listen_thread = std::make_shared<std::thread>([this] {
        while (running) {
            try {
                print_to_console("Waiting for a new connection");
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
    running = 0;
    _socket.reset();
    // Not sure how to shutdown thread properly. This approach can hang an application
    // if closing socket does not wake up blocked on `accept` method thread for some reason.
    _listen_thread->join();
    print_to_console("Server was shut down successfully.");
}

void server::handle_connection(std::unique_ptr<stream_socket> client_socket) {
    print_to_console("Received new connection.");
    question_session session;
    try {
        while (true) {
            auto data = receive(client_socket.get());
            std::string type = "invalid";
            auto request = client_message::deserialize(data);
            switch (request->get_type()) {
                case START_TEST:
                    type = "start";
                    session.start_test();
                    break;
                case NEXT_QUESTION: {
                    type = "next";
                    auto text = session.next_question();
                    send(question_message(text).serialize(), client_socket.get());
                    break;
                }
                case CHECK_ANSWER:
                    type = "answer";
                    if (!session.is_test_started()) {
                        print_to_console("Client sends answer before asking a question -_-");
                        break;
                    }
                    session.check_answer(std::dynamic_pointer_cast<check_message>(request)->get_user_answer());
                    break;
                case SEND_RESULTS:
                    type = "results";
                    send(results_message(session.get_results()).serialize(), client_socket.get());
                    break;
                default:
                    print_to_console("Received invalid request from client");
                    break;
            }
            print_to_console("Received msg [" + type + "]");

        }
    } catch (network_exception &e) {
        print_to_console(e.what());
        print_to_console("Connection lost.");
    }
}

void server::print_to_console(const std::string &msg) {
    std::cout << std::endl << "[LOG] " << msg;
    std::cout.flush();

}
