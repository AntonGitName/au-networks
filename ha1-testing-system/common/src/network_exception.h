//
// Created by antonpp on 05.04.17.
//

#ifndef HA1_TESTING_SYSTEM_NETWORK_EXCEPTION_H
#define HA1_TESTING_SYSTEM_NETWORK_EXCEPTION_H


#include <exception>
#include <string>

class network_exception : std::exception {
public:
    network_exception(const std::string &msg);

    const char *what() const noexcept override;

private:
    const std::string msg;

};


#endif //HA1_TESTING_SYSTEM_NETWORK_EXCEPTION_H
