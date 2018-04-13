#!/usr/bin/env bash

# input $1=target $2=password $3=file

(
    echo -n $1 | sha256sum -b | xxd -r -p -
    echo -n $2 | sha256sum -b | xxd -r -p -
    sha256sum -b $3 | xxd -r -p -
) | sha256sum -b | xxd -r -p - | head --bytes=16 | base64

