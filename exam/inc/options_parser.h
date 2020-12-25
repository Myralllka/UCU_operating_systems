#ifndef MYCAT_CONFIG_FILE_H
#define MYCAT_CONFIG_FILE_H

#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include <fstream>

class command_line_options {
public:
    command_line_options();

    ~command_line_options() = default;

    [[nodiscard]] std::vector<std::string> get_filenames() const { return filenames; };

    void parse(int ac, char **av);

private:
    std::vector<std::string> filenames;

    void init_opt_description();

    boost::program_options::variables_map var_map{};
    boost::program_options::options_description opt_conf{
            "Config File Options:\n\tmyrls [-h|--help] [file/directory] (./ by default)\n"};
};

#endif //MYCAT_CONFIG_FILE_H

