// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <boost/mpi.hpp>

#include "master.h"
#include "slave.h"

int main(int argc, char *argv[]) {
    boost::mpi::environment env{argc, argv};
    boost::mpi::communicator world{};

    if (world.rank() == MASTER_ID)
        master_code(world);
    else
        slave_code(world);

    std::cout << "FINISH process with rank " << world.rank() << " of " << world.size() << std::endl;
    return 0;
}