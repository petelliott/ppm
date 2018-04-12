#ifndef PASSWORD_H
#define PASSWORD_H

#define SECRET_BLOCK_READ 1024
#define PW_ENTROPY 16

void get_password(char *system, char *account, char *master_pass, int secret_fd);

#endif
