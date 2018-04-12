#include "password.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "useage: %s <site> <user> <secret>\n", argv[0]);
        exit(1);
    }

    // TODO: getpass is obsolete
    char *password = getpass("password");
    int secret_fd = open(argv[3], O_RDONLY);

    get_password(argv[1], argv[2], password, secret_fd);

    close(secret_fd);
    free(password);
}
