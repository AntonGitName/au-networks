//
// Created by antonpp on 05.04.17.
//

#include "network_exception.h"

const char *network_exception::what() const noexcept {
    return msg.c_str();
}

network_exception::network_exception(const std::string &msg) : msg(msg) {}
