//
// Created by antonpp on 05.04.17.
//

#pragma once


#include <exception>
#include <string>

class network_exception : std::exception {
public:
    network_exception(const std::string &msg);

    const char *what() const noexcept override;

private:
    const std::string msg;
};
