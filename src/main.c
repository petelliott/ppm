/*
the main program of ppm
Copyright (C) 2017  Peter Elliott

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "password.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv) {
    char *secret_file_name = "/dev/null";
    char *password = "";
    char *target = "";
    int pass_flag = 0;

    int c;
    while ((c = getopt (argc, argv, "t:s:p")) != -1) {
        switch (c) {
            case 't':
                target = optarg;
                break;
            case 's':
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


    get_password(target, password, secret_fd);

    close(secret_fd);
    if (pass_flag) {
        free(password);
    }
}
