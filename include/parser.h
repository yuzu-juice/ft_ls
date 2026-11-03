#ifndef PARSER_H_
# define PARSER_H_

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "type.h"

t_args parse_args(size_t, char **);

#endif
