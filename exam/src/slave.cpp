// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by myralllka on 12/24/20.
//

#include <pwd.h>
#include <unistd.h>
#include <filesystem>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "slave.h"
#include "master.h"
#include "inner_commands.h"

const std::map<std::string, std::function<int(std::vector<std::string> &)>> inner_commands = {
        {"fls",     list_files},
        {"fadd",    add_file},
        {"fopen",   open_file},
        {"fcl",     write_close_file},
        {"fshow",   show_file},
        {"ladd",    add_line},
        {"lrm",     remove_line}
};

void slave_code(const boost::mpi::communicator &world) {
    authentication(world);
    std::filesystem::create_directory("db");
    data_base_server(world);
}

void data_base_server(const boost::mpi::communicator &world) {
    std::string message;
    std::vector<std::string> splited_message;
    int status;
    bool flag = false;
    while (true) {
        message.reserve(MSG_SIZE);
        world.recv(MASTER_ID, COMMAND, message);
        if (message.empty()) {
            world.send(MASTER_ID, COMMAND, "empty message. try again!");
            continue;
        }
        message = decode_msg(message);
        splited_message = split_line(message);
        if (splited_message[0] == "q") {
            world.send(MASTER_ID, COMMAND, encode_msg("quit"));
            break;
        }
        for (auto &command : inner_commands) {
            if (command.first == splited_message[0]) {
                status = command.second(splited_message);
                if (status != 0) {
                    world.send(MASTER_ID, COMMAND, encode_msg("error occurred while executing."));
                } else {
                    world.send(MASTER_ID, COMMAND, encode_msg("true"));
                }
                flag = true;
            }
        }
        if (not flag) {
            world.send(MASTER_ID, COMMAND, encode_msg("bad command. try h to see all possible commands"));
        }
        flag = false;
    }
}

std::vector<std::string> split_line(std::string &line) {
    std::vector<std::string> result;
    boost::split(result, line, boost::is_any_of(" "));
    return result;
}

std::string get_password() {
    uid_t uid = geteuid();
    struct passwd *pw = getpwuid(uid);
    return pw ? static_cast<std::string>(pw->pw_name) : "";
}

void authentication(const boost::mpi::communicator &world) {
    std::string response, input;
    input.reserve(MSG_SIZE);
    response.reserve(MSG_SIZE);
    while (true) {
        world.recv(MASTER_ID, PASSWORD, input);
        input = decode_msg(input);
        if (check_password(input)) {
            response = encode_msg("true");
            world.send(MASTER_ID, PASSWORD, response);
            return;
        } else {
            response = encode_msg("false");
            world.send(MASTER_ID, PASSWORD, response);
        }
    }
}

bool check_password(const std::string &input) {
    std::string password = get_password();
    if (password.empty()) {
        std::cerr << "error while creating password" << std::endl;
    }
    return (input == password);
}