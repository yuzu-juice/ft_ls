#include "../include/parser.h"

t_option parse_options(size_t arg_count, char **args)
{
  bool end_of_option = false;
  t_option option = {0};

  for (size_t i = 0; i < arg_count; ++i)
  {
    if (strlen(args[i]) == 2 && strcmp(args[i], "--") == 0)
	end_of_option = true;
    // Start with "--"
    if (!end_of_option && strncmp(args[i], "--", 2) == 0)
      {
	if (strcmp(&args[i][2], "all") == 0)
	  option.all = true;
	else if (strcmp(&args[i][2], "reverse") == 0)
	  option.reverse = true;
	else if (strcmp(&args[i][2], "recursive") == 0)
	  option.recursive = true;
	else
	  {
	    dprintf(STDOUT_FILENO, "ft_ls: unrecognized option '%s'\n", args[i]);
	    exit (2);
	  }
      }
    // else if start with "-"
    else if (!end_of_option && strncmp(args[i], "-", 1) == 0)
      {
	for (size_t j = 1; args[i][j] != '\0'; ++j)
	  {
	    switch (args[i][j])
	      {
	      case 'a':
		option.all = true;
		break ;
	      case 'l':
		option.long_listing_format = true;
		break ;
	      case 'r':
		option.reverse = true;
		break ;
	      case 'R':
		option.recursive = true;
		break ;
	      case 't':
		option.sort_by_time = true;
		break ;
	      default:
		dprintf(STDOUT_FILENO, "ft_ls: unrecognized option '%s'\n", args[i]);
		exit (2);
	      }
	  }
      }
    // otherwise dirname or filename
    else
      {
	continue ;
      }

  }
    return option;
}
