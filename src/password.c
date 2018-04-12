#include "password.h"
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


/*
    generate the password for a certain target
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

    // output the password
    BIO *bio;
    BIO *b64;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new_fp(stdout, BIO_NOCLOSE);
    BIO_push(b64, bio);
    BIO_write(b64, out_hash, PW_ENTROPY);
    BIO_flush(b64);

    BIO_free_all(b64);
}
