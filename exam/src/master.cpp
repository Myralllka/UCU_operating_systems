// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by myralllka on 12/24/20.
//

#include <boost/mpi.hpp>

#include "master.h"
#include <syslog.h>

void master_code(const boost::mpi::communicator &world) {
    authentication_master(world);
    syslog(LOG_NOTICE, "logged in");
    data_base_client(world);
}

void data_base_client(const boost::mpi::communicator &world) {
    std::string message;
    message.reserve(MSG_SIZE);
    while (true) {
        message = readline("h for help > ");
        if (message == "h") {
            std::cout << "\nwelcome!\n\tpossible commands:"
                         "\n\tfls               list all files"
                         "\n\tfadd [filename]   add new file"
                         "\n\tfopen [filename]  open a cpecific file"
                         "\n\tfcl               close the opened file"
                         "\n\tfshow             show/cat the opened file"
                         "\n\tladd [line]       add a line to an opened file"
                         "\n\tlrm [number]  marked [d] a line in an opened file (numbers from 0)"
                         "\n\tq                 quit" << std::endl;
            continue;
        }
        message = encode_msg(message);
        world.send(SLAVE_ID, COMMAND, message);
        world.recv(SLAVE_ID, COMMAND, message);
        message = decode_msg(message);
        if (message == "true") {
            continue;
        } else if (message == "quit") return;
        else std::cout << "<here>: " << message << std::endl;
    }
}

void authentication_master(const boost::mpi::communicator &world) {
    std::string message = "password: ", password, response;
    message.reserve(MSG_SIZE);
    response.reserve(MSG_SIZE);
    password.reserve(MSG_SIZE);
    while (true) {
        password = encode_msg(readline(message.c_str()));
//        world.sendrecv(SLAVE_ID, PASSWORD, password, SLAVE_ID, PASSWORD, password);
        world.send(SLAVE_ID, PASSWORD, password);
        world.recv(SLAVE_ID, PASSWORD, response);
        response = decode_msg(static_cast<std::string>(response));
//        if (response == "start") {
//            while (not (response == "stop")) {
//                world.recv(SLAVE_ID, LONG_MESSAGE, response);
//            }
//        }
        if (response == "true") {
            std::cout << "welcome, " << decode_msg(password) << std::endl;
            return;
        } else {
            message = "incorrect password. try again: ";
        }
    }
}

std::string encode_msg(std::string buffer) {
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), [](int c) {
        if (isalpha(c) && (c = tolower(c)) && (c += 13) && c > 'z') c -= 26;
        return c;
    });
    return buffer;
}

std::string decode_msg(std::string buffer) {
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), [](int c) {
        if (isalpha(c) && (c = tolower(c)) && (c -= 13) && c < 'a') c += 26;
        return c;
    });
    return buffer;
}