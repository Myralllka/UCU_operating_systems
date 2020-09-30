#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char buf[512];

void mv(int fd1, int fd2) {
    int n;
    while ((n = read(fd1, buf, sizeof(buf))) > 0) {
        if (write(fd2, buf, n) != n) {
            printf(1, "mv: write error\n");
            exit();
        }
    }
    if (n < 0) {
        printf(1, "mv: read error\n");
        exit();
    }
}

int main(int argc, char *argv[]) {
    int fd1, fd2;

    if (argc <= 1) {
        exit();
    }
    if (argc > 3) {
        printf(1, "mv: now supporting only two arguments, source and destination.\n");
        exit();
    }
    if ((fd1 = open(argv[1], 0)) < 0) {
        printf(1, "mv: cannot open %s\n", argv[1]);
        exit();
    }
    if ((fd2 = open(argv[2], O_WRONLY | O_CREATE)) < 0) {
        printf(1, "mv: cannot open %s\n", argv[2]);
        exit();
    }

    mv(fd1, fd2);
    close(fd1);
    close(fd2);
    unlink(argv[1]);
    exit();
}
