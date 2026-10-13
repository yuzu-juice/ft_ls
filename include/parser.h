#ifndef PARSER_H
# define PARSER_H

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
