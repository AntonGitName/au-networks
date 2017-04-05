//
// Created by antonpp on 05.04.17.
//

#include "client.h"

client::client(std::string hostname, int port) : client_socket(new tcp_client_socket(hostname, port)) {}
