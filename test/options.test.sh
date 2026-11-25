#!/bin/sh
. test/common.sh

compare -a "$fixture"
compare -l "$fixture"
compare -r "$fixture"
compare -R "$fixture"
compare -t "$fixture"
compare --all "$fixture"
compare --reverse "$fixture"
compare --recursive "$fixture"
