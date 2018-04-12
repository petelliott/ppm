/*
the get_password funtion of ppm
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
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


/*
    create a password from:
        target:      the account you want generate the password for
        master_pass: the password for your package manager
        secret_fd:   the file to read your secret from

    the system works by sha256 hashing each field, hashing the
    resultant hshes, then outputing
    the resultant password to stdio in base64.
    
    the password entropy (in bytes) can be be set with
    PW_ENTROPY in password.h
*/
void get_password(char *target, char *master_pass, int secret_fd) {
    
    char targ_hash[SHA256_DIGEST_LENGTH];
    char pass_hash[SHA256_DIGEST_LENGTH];
    char secret_hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;

    // calculate the identity hash
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, target, strlen(target));
    SHA256_Final(targ_hash, &sha256);

    // calculate the password hash
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, master_pass, strlen(master_pass));
    SHA256_Final(pass_hash, &sha256);

    // calculate the secret hash
    SHA256_Init(&sha256);
    char secret_read[SECRET_BLOCK_READ];
    int bytes_read;
    do {
        bytes_read = read(secret_fd, secret_read, SECRET_BLOCK_READ); 
        // NOTE: one update will have size 0
        SHA256_Update(&sha256, secret_read, bytes_read);
    } while(bytes_read > 0);
    SHA256_Final(secret_hash, &sha256);

    // generate the output hash
    char out_hash[SHA256_DIGEST_LENGTH];
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, targ_hash, SHA256_DIGEST_LENGTH);
    SHA256_Update(&sha256, pass_hash, SHA256_DIGEST_LENGTH);
    SHA256_Update(&sha256, secret_hash, SHA256_DIGEST_LENGTH);
    SHA256_Final(out_hash, &sha256);

    // output the password in base64
    BIO *bio;
    BIO *b64;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_fp(stdout, BIO_NOCLOSE);
    BIO_push(b64, bio);
    BIO_write(b64, out_hash, PW_ENTROPY);
    BIO_flush(b64);

    BIO_free_all(b64);
}
