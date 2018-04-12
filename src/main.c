#include "password.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    if (argc != 4) {
        fputs(stderr, "useage: %s <site> <user> <secret>\n", argv[0]);
        exit(1);
    }

    // TODO: getpass is obsolete
    char *password = getpass("password");

    get_password(argv[1], argv[2], password, argv[3]);

    free(password);
}
