//
// Created by myralllka on 12/25/20.
//

#ifndef EXAM_INNER_COMMANDS_H
#define EXAM_INNER_COMMANDS_H

int list_files(const std::vector<std::string> &args);

int add_file(const std::vector<std::string> &args);

int open_file(const std::vector<std::string> &args);

int write_close_file(const std::vector<std::string> &args);

int show_file(const std::vector<std::string> &args);

int add_line(const std::vector<std::string> &args);

int remove_line(const std::vector<std::string> &args);

#endif //EXAM_INNER_COMMANDS_H
