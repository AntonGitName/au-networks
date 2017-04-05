//
// Created by antonpp on 05.04.17.
//

#pragma once

#include <exception>
#include <string>
#include <vector>

class serialization_exception : std::exception {
public:
    serialization_exception(const std::string &msg);

    const char *what() const noexcept override;

private:
    const std::string msg;
};

class serializable {
    virtual std::vector<char> serialize() const = 0;
};
