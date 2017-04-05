//
// Created by antonpp on 05.04.17.
//

#pragma once

#include <memory>

#include "util.h"
#include "serializable.h"

/*
 * Client
 */

enum client_message_type {
    START_TEST, NEXT_QUESTION, CHECK_ANSWER, SEND_RESULTS
};

struct client_message : serializable {
    virtual client_message_type get_type() const = 0;

    std::vector<char> serialize() const {
        return {(char) get_type()};
    }

    static std::shared_ptr<client_message> deserialize(const char *data, size_t length);
};

struct start_message : client_message {
    client_message_type get_type() const { return START_TEST; }
};

struct next_message : client_message {
    client_message_type get_type() const { return NEXT_QUESTION; }
};

struct check_message : client_message {
    check_message(int x) : user_answer(x) {}

    client_message_type get_type() const { return CHECK_ANSWER; }

    int get_user_answer() const { return user_answer; }

    std::vector<char> serialize() const {
        auto result = client_message::serialize();
        util::append_int_to_bytes(result, user_answer);
        return result;
    }

private:
    const int user_answer;
};

struct send_message : client_message {
    client_message_type get_type() const { return SEND_RESULTS; }
};

/*
 * Server
 */

enum question_verdict {
    CORRECT, WRONG, NO_ANSWER
};

enum server_message_type {
    QUESTION, RESULTS
};

struct server_message : serializable {
    virtual server_message_type get_type() const = 0;

    std::vector<char> serialize() const {
        return {(char) get_type()};
    }

    static std::shared_ptr<server_message> deserialize(const char *data, size_t length);
};

struct question_message : server_message {
    question_message(const std::string &text) : text(text) {}

    server_message_type get_type() const { return QUESTION; }

    std::string get_text() const { return text; }

    std::vector<char> serialize() const;

private:
    const std::string text;
};

struct results_message : server_message {
    results_message(const std::vector<question_verdict> &verdicts) : verdicts(verdicts) {}

    std::vector<char> serialize() const;

    server_message_type get_type() const { return RESULTS; }

    std::vector<question_verdict> get_verdicts() const { return verdicts; }

private:
    const std::vector<question_verdict> verdicts;
};