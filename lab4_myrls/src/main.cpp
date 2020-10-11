// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <ftw.h>
#include <pwd.h>
#include "options_parser.h"
#include <ctime>
#include <sys/stat.h>
#include <boost/algorithm/string/case_conv.hpp>

std::string getUser(uid_t uid) {
    struct passwd *pws;
    pws = getpwuid(uid);
    return pws->pw_name;
}

typedef std::tuple<std::string, struct stat, int> file_description;
std::map<std::string, std::vector<file_description>> dirs;

static int save_names([[maybe_unused]] const char *fpath,
                      [[maybe_unused]] const struct stat *sb,
                      [[maybe_unused]] const int tflag,
                      [[maybe_unused]] struct FTW *ftwbuf) {
    std::string filename = fpath;
    if (tflag == FTW_D) {
        dirs[filename].emplace_back(filename, *sb, tflag);
    }
    if (ftwbuf->level > 0 or tflag == FTW_F) {
        dirs[filename.substr(0,
                             filename.find_last_of(basename(filename.data())) -
                             strlen(basename(filename.data())))
        ].emplace_back(filename, *sb, tflag);
    }
    return 0;
}

bool compare_nocase(const std::string &first, const std::string &second) {
    size_t i = 0;
    while ((i < first.length()) && (i < second.length())) {
        if (tolower(first[i]) < tolower(second[i])) return true;
        else if (tolower(first[i]) > tolower(second[i])) return false;
        ++i;
    }
    return (first.length() < second.length());
}

int main(int argc, char **argv) {

    command_line_options conf;
    conf.parse(argc, argv);
    if (conf.get_filenames().size() > 1) {
        std::cerr << "myrls: too many arguments" << std::endl;
    }
    bool flags = false;

    if (nftw((conf.get_filenames().empty()) ? "." : conf.get_filenames()[0].data(),
             save_names,
             20,
             flags | FTW_NS | FTW_MOUNT | FTW_PHYS | FTW_DEPTH) != -1) {
    } else {
        std::cerr << "ntfw error" << std::endl;
        return -1;
    }

    for (auto &dir_entry: dirs) {
        std::sort(dir_entry.second.begin(), dir_entry.second.end(),
                  [](file_description a, file_description b) {
                      return compare_nocase(std::get<0>(a), std::get<0>(b));
                  });
    }
    std::string buff;
    char *linkname = new char[256];
    buff.reserve(255);
    for (auto &dir_entry: dirs) {
        std::cout << "\n" << dir_entry.first << ":\n";
        for (auto &file: dir_entry.second) {
            auto sb = std::get<1>(file);
            buff.clear();

            strftime(buff.data(), 255, "%d.%m.%Y %H:%M:%S", localtime(&sb.st_mtim.tv_sec));
            if (auto tmp = (S_ISLNK(sb.st_mode) ? readlink(std::get<0>(file).c_str(), linkname, 255) : -1)) {
                linkname[tmp] = '\0';
            }
            
            std::cout << ((sb.st_mode & S_IRUSR) ? "r" : "-")
                      << ((sb.st_mode & S_IWUSR) ? "w" : "-")
                      << ((sb.st_mode & S_IXUSR) ? "x" : "-")
                      << ((sb.st_mode & S_IRGRP) ? "r" : "-")
                      << ((sb.st_mode & S_IWGRP) ? "w" : "-")
                      << ((sb.st_mode & S_IXGRP) ? "x" : "-")
                      << ((sb.st_mode & S_IROTH) ? "r" : "-")
                      << ((sb.st_mode & S_IWOTH) ? "w" : "-")
                      << ((sb.st_mode & S_IXOTH) ? "x" : "-")
                      << " " << getUser(sb.st_uid).data() << "\t"
                      << static_cast<intmax_t>(sb.st_size) << "\t"
                      << buff.data() << "\t"
                      << (((S_IEXEC & sb.st_mode || !S_ISREG(sb.st_mode))) ? ((S_ISDIR(sb.st_mode)) ? "/" : \
                      (S_ISLNK(sb.st_mode)) ? "@" : \
                      (S_IEXEC & sb.st_mode) ? "*" : \
                      (S_ISSOCK(sb.st_mode)) ? "=" : \
                      (S_ISFIFO(sb.st_mode)) ? "|" : "?") : "")
                      << basename(std::get<0>(file).data())
                      << ((S_ISLNK(sb.st_mode)) ? " => " : "")
                      << ((S_ISLNK(sb.st_mode)) ? linkname : "")
                      << std::endl;
        }
    }
    delete[] linkname;
    return 0;
}
