#ifndef PARSER_H_
#define PARSER_H_

#include <bits/getopt_ext.h>
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "type.h"

t_args parse_args(size_t, char **);

#endif
