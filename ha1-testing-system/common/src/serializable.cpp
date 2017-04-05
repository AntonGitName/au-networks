//
// Created by antonpp on 05.04.17.
//

#include "serializable.h"

serialization_exception::serialization_exception(const std::string &msg) : msg(msg) {}

const char *serialization_exception::what() const noexcept {
    return msg.c_str();
}

