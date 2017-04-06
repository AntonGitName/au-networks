//
// Created by antonpp on 06.04.17.
//

#include "question_session.h"

std::string question_session::next_question() {
    int a = (int) (random() % 100);
    int b = (int) (random() % 100);
    last_question_answer = a * b;
    verdicts.push_back(protocol::NO_ANSWER);
    return std::to_string(a) + " * " + std::to_string(b) + " = ?";
}

void question_session::start_test() {
    verdicts.clear();
    last_question_answer = -1;
}

std::vector<protocol::question_verdict> question_session::get_results() {
    return verdicts;
}

void question_session::check_answer(int x) {
    verdicts.back() = ((x == last_question_answer) ? protocol::CORRECT : protocol::WRONG);
}

bool question_session::is_test_started() const {
    return last_question_answer != -1;
}
