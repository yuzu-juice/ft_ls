#include "../include/parser.h"

static t_args init_args(size_t);

t_args parse_args(size_t ac, char **av)
{
  bool end_of_option = false;

  t_args args = init_args(ac);

  for (size_t i = 0; i < ac; ++i)
  {
    if (strlen(av[i]) == 2 && strcmp(av[i], "--") == 0)
      {
	end_of_option = true;
	continue ;
      }
    // Start with "--"
    if (!end_of_option && strncmp(av[i], "--", 2) == 0)
      {
	if (strcmp(&av[i][2], "all") == 0)
	  args.options.all = true;
	else if (strcmp(&av[i][2], "reverse") == 0)
	  args.options.reverse = true;
	else if (strcmp(&av[i][2], "recursive") == 0)
	  args.options.recursive = true;
	else
	  {
	    dprintf(STDERR_FILENO, "ft_ls: unrecognized option '%s'\n", av[i]);
	    free(args.paths);
	    exit (2);
	  }
      }
    // else if start with "-"
    else if (!end_of_option && strncmp(av[i], "-", 1) == 0 && strlen(av[i]) >= 2)
      {
	for (size_t j = 1; av[i][j] != '\0'; ++j)
	  {
	    switch (av[i][j])
	      {
	      case 'a':
		args.options.all = true;
		break ;
	      case 'l':
		args.options.long_listing_format = true;
		break ;
	      case 'r':
		args.options.reverse = true;
		break ;
	      case 'R':
		args.options.recursive = true;
		break ;
	      case 't':
		args.options.sort_by_time = true;
		break ;
	      default:
		dprintf(STDERR_FILENO, "ft_ls: invalid option -- '%c'\n", av[i][j]);
		free(args.paths);
                exit (2);
	      }
	  }
      }
      // otherwise dirname or filename
    else {
        args.paths[args.path_count] = av[i];
	++args.path_count;
    }
  }
  if (!args.paths[0])
    {
      args.paths[0] = ".";
      ++args.path_count;
    }
  return args;
}

static t_args init_args(size_t ac)
{
  t_args args;
  t_options options;
  options = (t_options){0};
  args.options = options;
  // Allocating space based on `argc` might result in some excess, but it'll be sufficient.
  args.paths = malloc(sizeof(char *) * ac + 1);
  if (!args.paths)
    exit(2);
  args.paths[0] = NULL;
  args.path_count = 0;
  return args;
}
