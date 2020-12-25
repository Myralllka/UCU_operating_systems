//
// Created by myralllka on 12/24/20.
//

#ifndef TEST_MASTER_H
#define TEST_MASTER_H

#include <boost/mpi.hpp>
#include "readline/readline.h"

#define MASTER_ID       0
#define SLAVE_ID        1

#define PASSWORD        2
#define COMMAND         3
#define LONG_MESSAGE    4
#define MSG_SIZE        8191

void master_code(const boost::mpi::communicator &world);

std::string encode_msg(std::string buffer);

std::string decode_msg(std::string buffer);

void authentication_master(const boost::mpi::communicator &world);

void data_base_client(const boost::mpi::communicator &world);


#endif //TEST_MASTER_H
