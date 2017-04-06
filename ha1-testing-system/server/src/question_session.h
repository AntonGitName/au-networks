//
// Created by antonpp on 06.04.17.
//

#pragma once


#include <string>
#include <memory>
#include <iostream>
#include <thread>

#include "tcp_server_socket.h"
#include "protocol.h"


class question_session {
public:
    void start_test();

    std::vector<protocol::question_verdict> get_results();

    std::string next_question();

    void check_answer(int x);

    bool is_test_started() const;

private:
    std::vector<protocol::question_verdict> verdicts;
    int last_question_answer = -1;
};

