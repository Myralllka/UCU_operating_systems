//
// Created by myralllka on 12/24/20.
//

#ifndef TEST_SLAVE_H
#define TEST_SLAVE_H

#include <boost/mpi.hpp>
#include <map>

std::vector<std::string> split_line(std::string &line);

void slave_code(const boost::mpi::communicator &world);

std::string get_password();

bool check_password(const std::string &input);

void authentication(const boost::mpi::communicator &world);

void data_base_server(const boost::mpi::communicator &world);

#endif //TEST_SLAVE_H
