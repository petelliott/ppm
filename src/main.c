#include "password.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    char *secret_file_name = "/dev/null";
    char *password = "";
    char *user = "";
    char *site = "";
    int pass_flag = 0;

    int c;
    while ((c = getopt (argc, argv, "u:s:f:p")) != -1) {
        switch (c) {
            case 'u':
                user = optarg;
            case 's':
                site = optarg;
                break;
            case 'f':
                secret_file_name = optarg;
                break;
            case 'p':
                pass_flag = 1;
                break;
        } 
    }

    int secret_fd = open(secret_file_name, O_RDONLY);
    if (secret_fd < 0) {
        perror(secret_file_name);
        exit(1);
    }
    
    if (pass_flag) {
        // TODO: getpass is obsolete
        password = getpass("password:");
    }


    get_password(site, user, password, secret_fd);

    close(secret_fd);
    if (pass_flag) {
        free(password);
    }
}
