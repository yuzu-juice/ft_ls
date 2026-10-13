#include "../include/ls.h"

/*
  cwd_file points to a vector of t_fileinfo, one per file.
  cwd_n_alloc is the nunmber of elements space has been allocated for.
  cwd_n_used is the number actually in use.
*/

static t_fileinfo *cwd_file;
static size_t cwd_n_alloc;
static size_t cwd_n_used;

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  
  printf("Hello, world!");
  return 0;
}
