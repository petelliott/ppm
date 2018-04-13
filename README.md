# Peter's Password Manager

[![Build Status](https://travis-ci.org/Petelliott/ppm.svg?branch=master)](https://travis-ci.org/Petelliott/ppm)

## useage

example:
```
$ ./ppm -t petelliott:github.com -s secret_file -p
password:
GgPAL7Ux1+HONTsvIHEceQ==
$
```

no arguments are mandatory

- `-t` the target that the password is for.
- `-s` the file to read the secret from.
- `-p` require a master password

## system

password := base64(128bits(sha256(sha256(target)+sha256(password)+sha256(secret))))

## installation

```
ppm$ make
```

in your bashrc:
```
alias ppm="pathto/ppm -ps secret_file -t"
```
