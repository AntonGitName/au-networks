//
// Created by antonpp on 05.04.17.
//

#include "protocol.h"

namespace protocol {

    using namespace util;

    std::shared_ptr<client_message> client_message::deserialize(const char *data, size_t length) {
        if (!length) {
            throw serialization_exception("empty message");
        }
        ++data;
        --length;
        switch (data[-1]) {
            case START_TEST:
                return std::make_shared<start_message>();
            case NEXT_QUESTION:
                return std::make_shared<next_message>();
            case SEND_RESULTS:
                return std::make_shared<send_message>();
            case CHECK_ANSWER:
                return std::make_shared<check_message>(
                        read_int_from_bytes(data, (size_t) std::min((size_t) 4, length)));
            default:
                throw serialization_exception("unknown message type");
        }
    }

    std::shared_ptr<server_message> server_message::deserialize(const char *data, size_t length) {
        if (!length) {
            throw serialization_exception("empty message");
        }
        ++data;
        --length;
        switch (data[-1]) {
            case QUESTION: {
                auto l = read_int_from_bytes(data, (size_t) std::min((size_t) 4, length));
                auto s = read_string_from_bytes(data + 4, (size_t) (length - 4), (size_t) l);
                if (l != length - 4) {
                    throw serialization_exception("Message is bigger then it should be");
                }
                return std::make_shared<question_message>(s);
            }
            case RESULTS: {
                auto l = read_int_from_bytes(data, (size_t) std::min((size_t) 4, length));
                data += 4;
                length -= 4;
                std::vector<question_verdict> res;
                for (int i = 0; i < l; ++i) {
                    int verdict = read_int_from_bytes(data, (size_t) std::min((size_t) 4, length));
                    if (verdict != NO_ANSWER && verdict != CORRECT && verdict != WRONG) {
                        throw serialization_exception("Unknown answer verdict");
                    }
                    res.push_back((question_verdict) verdict);
                    data += 4;
                    length -= 4;
                }
                if (length) {
                    throw serialization_exception("Message is bigger then it should be");
                }
                return std::make_shared<results_message>(res);
            }
            default:
                throw serialization_exception("unknown message type");
        }

    }

    std::vector<char> results_message::serialize() const {
        auto result = server_message::serialize();
        int n = (int) verdicts.size();
        append_int_to_bytes(result, n);
        for (int i = 0; i < n; ++i) {
            append_int_to_bytes(result, (int) verdicts[i]);
        }
        return result;

    }

    std::vector<char> question_message::serialize() const {
        auto result = server_message::serialize();
        append_string_to_bytes(result, text);
        return result;
    }
}