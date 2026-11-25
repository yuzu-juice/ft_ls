#ifndef FILELIST_H_
# define FILELIST_H_

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <strings.h>
#include <stdint.h>
#include <grp.h>
#include <time.h>

#include "type.h"

t_filelist init_filelist(char *, bool);
void free_filelist(t_filelist *);

#endif
