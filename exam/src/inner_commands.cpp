// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Created by myralllka on 12/25/20.
//

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "inner_commands.h"
#include "master.h"

std::string opened_file_name;

int list_files(const std::vector<std::string> &args) {
    if (args.size() != 1) {
        return -1;
    }
    std::cout << "\n";
    for (const auto &entry : std::filesystem::directory_iterator("db")) {
        std::cout << entry.path() << ", ";
    }
    std::cout << std::endl;
    return 0;
}

int open_file(const std::vector<std::string> &args) {
    if (args.size() != 2) {
        return -1;
    }
    opened_file_name = "db/" + args[1];
    return 0;
}

int add_file(const std::vector<std::string> &args) {
    if (args.size() != 2 or std::filesystem::exists("db/" + args[1])) {
        return -1;
    }
    std::ofstream outfile("db/" + args[1]);
//    outfile << " ";
//    outfile.close();
    return 0;
}

int write_close_file(const std::vector<std::string> &args) {
    if (args.size() != 1) {
        return -1;
    }
    opened_file_name.clear();
    return 0;
}

int show_file(const std::vector<std::string> &args) {
    if (args.size() != 1) {
        return -1;
    }
    if (opened_file_name.empty()) return -1;
    std::fstream opened_file;
    opened_file.open(opened_file_name);
    std::string line;
    while (opened_file >> line) {
        std::cout << decode_msg(line) << std::endl;
    }
    opened_file.close();
    return 0;
}

int remove_line([[maybe_unused]] const std::vector<std::string> &args) {
    if (opened_file_name.empty()) return -1;
    if (args.size() != 2) {
        return -1;
    }
    std::fstream opened_file;
    opened_file.open(opened_file_name);
    size_t counter = 0, found, idx = static_cast<size_t>(std::stoi(args[1]));
    std::string line;

    while (opened_file >> line) {
        if (++counter == idx) {
            found = line.find(encode_msg("[d]"));
            if (found == std::string::npos)
                opened_file << encode_msg("\n[d]");
        }
    }
    opened_file.close();
    return 0;
}

int add_line(const std::vector<std::string> &args) {
    if (args.size() < 2) {
        return -1;
    }
    if (opened_file_name.empty()) return -1;
    std::fstream opened_file;
    opened_file.open(opened_file_name, std::ios_base::app);
    for (const auto &x : boost::make_iterator_range(args.begin() + 1, args.end())) {
        opened_file << encode_msg(x);
    }
    opened_file << "\n";
    opened_file.close();
    return 0;
}