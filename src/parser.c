#include "../include/parser.h"

t_args init_args(void)
{
  t_args args;

  args.filenames = NULL;
  args.all = false;
  args.long_listing_format = false;
  args.reverse = false;
  args.recursive = false;
  args.sort_by_time = false;

  return args;
}

t_args parse_args(size_t ac, char **av)
{
  bool end_of_option = false;

  t_args args = init_args();

  for (size_t i = 0; i < ac; ++i)
  {
    if (strlen(av[i]) == 2 && strcmp(av[i], "--") == 0)
	end_of_option = true;
    // Start with "--"
    if (!end_of_option && strncmp(av[i], "--", 2) == 0)
      {
	if (strcmp(&av[i][2], "all") == 0)
	  args.all = true;
	else if (strcmp(&av[i][2], "reverse") == 0)
	  args.reverse = true;
	else if (strcmp(&av[i][2], "recursive") == 0)
	  args.recursive = true;
	else
	  {
	    dprintf(STDOUT_FILENO, "ft_ls: unrecognized option '%s'\n", av[i]);
	    exit (2);
	  }
      }
    // else if start with "-"
    else if (!end_of_option && strncmp(av[i], "-", 1) == 0)
      {
	for (size_t j = 1; av[i][j] != '\0'; ++j)
	  {
	    switch (av[i][j])
	      {
	      case 'a':
		args.all = true;
		break ;
	      case 'l':
		args.long_listing_format = true;
		break ;
	      case 'r':
		args.reverse = true;
		break ;
	      case 'R':
		args.recursive = true;
		break ;
	      case 't':
		args.sort_by_time = true;
		break ;
	      default:
		dprintf(STDOUT_FILENO, "ft_ls: unrecognized option '%s'\n", av[i]);
		exit (2);
	      }
	  }
      }
    // otherwise dirname or filename
    else
      {
	// append to list of filenames.
      }

  }
    return args;
}
