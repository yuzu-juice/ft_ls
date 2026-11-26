#include "../include/ft_ls.h"

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  t_args args = parse_args((size_t)argc - 1, argv + 1);
  bool has_multi_dir = args.path_count == 1 ? false : true;

  t_stack stack = {0};
  for (size_t i = args.path_count; i > 0; --i) {
    stack_push(&stack, args.paths[i - 1]);
  }
  free(args.paths);

  char *path;
  while ((path = stack_pop(&stack)) != NULL) {
    t_filelist fl = init_filelist(path, args.options.all);
    if (args.options.sort_by_time)
      qsort(fl.files, fl.count, sizeof(*fl.files), compare_timestamp);
    else
      qsort(fl.files, fl.count, sizeof(*fl.files), compare_filename);
    if (args.options.reverse)
      reverse_filelist(&fl);
    if (has_multi_dir || args.options.recursive)
      printf("%s:\n", path);

    print_filelist(&fl, &args.options);

    if (args.options.recursive) {
      for (size_t i = fl.count; i > 0; --i) {
        const t_fileinfo *file = &fl.files[i - 1];
        if (strcmp(file->name, ".") == 0 || strcmp(file->name, "..") == 0)
          continue;

        if (S_ISDIR(fl.files[i - 1].stat.st_mode)) {
          char *full_path = join_path(path, file->name);
          stack_push(&stack, full_path);
          free(full_path);
        }
      }
    }
    if ((has_multi_dir || args.options.recursive) && stack.count > 0)
      printf("\n");

    free_filelist(&fl);
    free(path);
  }
  stack_free(&stack);

  return 0;
}
