#include <stdio.h>
#include <dirent.h>
#include "../include/type.h"

void print_fileinfo(struct dirent ent, t_args args) {
  (void)args;
  printf("%s", ent.d_name);
}
