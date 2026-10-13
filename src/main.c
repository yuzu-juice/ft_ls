#include "../include/ls.h"
#include "../include/parser.h"

/*
  cwd_file points to a vector of t_fileinfo, one per file.
  cwd_n_alloc is the nunmber of elements space has been allocated for.
  cwd_n_used is the number actually in use.
*/

static t_fileinfo *cwd_file;
static size_t cwd_n_alloc;
static size_t cwd_n_used;

int main(int argc, char **argv) {
  (void)cwd_file;
  (void)cwd_n_alloc;
  (void)cwd_n_used;

  t_option opt = parse_options((size_t)argc - 1, argv + 1);
  printf("-a: %d\n-l: %d\n-r: %d\n-R: %d\n-t: %d\n", opt.all, opt.long_listing_format, opt.reverse, opt.recursive, opt.sort_by_time);
  return 0;
}
