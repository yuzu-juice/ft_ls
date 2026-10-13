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

  t_args args = parse_args((size_t)argc - 1, argv + 1);
  
  printf("-a: %d\n-l: %d\n-r: %d\n-R: %d\n-t: %d\n", args.all, args.long_listing_format, args.reverse, args.recursive, args.sort_by_time);
  
  return 0;
}
