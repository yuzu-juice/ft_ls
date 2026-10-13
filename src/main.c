#include "../include/ls.h"
#include "../include/parser.h"
#include "../include/list.h"

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

  // ft_printlst(args.filename);
  
  // printf("-a: %d\n-l: %d\n-r: %d\n-R: %d\n-t: %d\n", args.all, args.long_listing_format, args.reverse, args.recursive, args.sort_by_time);

  t_list *filename = args.filename;
  bool has_multi_dir = ft_lstsize(filename) == 1 ? false : true;
  
  while (filename)
    {
      DIR *path = opendir(filename->filename);
      if (path)
	{
	  struct dirent *ent = readdir(path);
	  if (has_multi_dir)
	    printf("%s:\n", filename->filename);
	  while (ent)
	    {
	      if (!args.all && strncmp(ent->d_name, ".", 1) == 0)
		{
		  ent = readdir(path);
		  continue ;
		}
	      printf("%s", ent->d_name);
	      ent = readdir(path);
	      if (ent)
		printf("  ");
	      else
		printf("\n");
	    }
	  closedir(path);
	  if (has_multi_dir && filename->next)
	    printf("\n");
	}
      else
	{
	  dprintf(STDERR_FILENO, "ft_ls: cannot access '%s", filename->filename);
	  perror("'");
	}
      filename = filename->next;
    }
  ft_lstclear(&args.filename);
  
  return 0;
}
