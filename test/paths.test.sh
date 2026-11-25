#!/bin/sh
. test/common.sh

compare "$fixture/subdir"
compare "$fixture/missing"
