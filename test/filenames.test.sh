#!/bin/sh
. test/common.sh

compare Makefile
compare "$fixture/file"
compare "$fixture/.hidden"
compare "$fixture"
