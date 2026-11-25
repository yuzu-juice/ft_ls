#include "../include/type.h"
#include "../include/parser.h"
#include "../include/print.h"
#include "../include/filelist.h"

int main(int argc, char **argv) {
  t_args args = parse_args((size_t)argc - 1, argv + 1);
  bool has_multi_dir = args.path_count == 1 ? false : true;

  for (size_t i = 0; i < args.path_count; ++i) {
    t_filelist fl = init_filelist(args.paths[i], args.options.all);
    if (has_multi_dir)
      printf("%s:\n", args.paths[i]);

    print_filelist(&fl, &args.options);

    if (has_multi_dir && i != args.path_count - 1)
      printf("\n");
    free_filelist(&fl);
    }
  free(args.paths);
  return 0;
}
