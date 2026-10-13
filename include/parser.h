#ifndef PARSER_H_
# define PARSER_H_

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "list.h"

typedef struct s_args
{
  t_list *filename;
  bool all;
  bool long_listing_format;
  bool reverse;
  bool recursive;
  bool sort_by_time;
} t_args;

t_args parse_args(size_t, char **);

#endif
