#include "../include/type.h"
#include "../include/parser.h"
#include "../include/print.h"

static t_filelist init_filelist(t_args);
static void add_file(t_filelist *, char *);
static void free_filelist(t_filelist *);

int main(int argc, char **argv) {
  t_args args = parse_args((size_t)argc - 1, argv + 1);
  t_filelist fl = init_filelist(args);

  // printf("-a: %d\n-l: %d\n-r: %d\n-R: %d\n-t: %d\n", args.all, args.long_listing_format, args.reverse, args.recursive, args.sort_by_time);

  bool has_multi_dir;
  if (fl.count == 1)
    has_multi_dir = false;
  else
    has_multi_dir = true;
  
  for (size_t i = 0; i < fl.count; ++i)
    {
      DIR *path = opendir(fl.files[i].name);
      if (path)
	{
	  struct dirent *ent;
	  if (has_multi_dir)
            printf("%s:\n", fl.files->name);
          bool first = true;
	  while ((ent = readdir(path)) != NULL)
	    {
	      if (!args.options.all && strncmp(ent->d_name, ".", 1) == 0)
		continue ;
	      if (!first && !args.options.long_listing_format)
		dprintf(STDOUT_FILENO, "  ");
	      if (!first && args.options.long_listing_format)
                dprintf(STDOUT_FILENO, "\n");
	      print_fileinfo(*ent, args);
	      first = false;
	    }
	  printf("\n");
	  if (has_multi_dir && i == fl.count - 1)
	    printf("\n");
	  closedir(path);
	}
      else
	{
	  dprintf(STDERR_FILENO, "ft_ls: cannot access '%s", fl.files->name);
	  perror("'");
	}
    }

  free_filelist(&fl);
  free(args.paths);
  return 0;
}

static t_filelist init_filelist(t_args args) {
  t_filelist fl = {0};

  for (size_t i = 0; i < args.path_count; ++i)
    add_file(&fl, args.paths[i]);
  return fl;
}

static void add_file(t_filelist *fl, char *path) {
  t_fileinfo *tmp;
  size_t new_capacity;

  if (fl->count == fl->capacity) {
    new_capacity = fl->capacity == 0 ? 1 : fl->capacity * 2;
    tmp = realloc(fl->files, new_capacity * sizeof(*tmp));
    if (!tmp)
      exit(2);
    fl->files = tmp;
    fl->capacity = new_capacity;
  }
  fl->files[fl->count] = (t_fileinfo){0};
  fl->files[fl->count].name = strdup(path);
  if (!fl->files[fl->count].name)
    exit(2);
  ++fl->count;
}

static void free_filelist(t_filelist *fl) {
  for (size_t i = 0; i < fl->count; ++i)
    free(fl->files[i].name);
  free(fl->files);
  *fl = (t_filelist){0};
}
