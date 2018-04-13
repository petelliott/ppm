#!/usr/bin/env bash

# exit our tests when they fail
set -e

# our info
SECRET="$(cat /dev/urandom | head --bytes=128 | base64)"
TARGET="$(cat /dev/urandom | head --bytes=32 | base64)"

REFERENCE=$(dirname $1)/test/reference.sh

[[ $(echo -n $SECRET | ./$1) == $(echo -n $SECRET | $REFERENCE "" "" /dev/null) ]]
[[ $(echo -n $SECRET | ./$1 -t "$TARGET") == $(echo -n $SECRET | $REFERENCE "$TARGET" "" /dev/null) ]]
[[ $(echo -n $SECRET | ./$1 -s /dev/stdin) == $(echo -n $SECRET | $REFERENCE "" "" /dev/stdin) ]]
[[ $(echo -n $SECRET | ./$1 -t $TARGET -s /dev/stdin) == $(echo -n $SECRET | $REFERENCE "$TARGET" "" /dev/stdin) ]]
#TODO: password tests
