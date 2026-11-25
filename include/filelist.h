#ifndef FILELIST_H_
#define FILELIST_H_

#include "type.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

t_filelist init_filelist(char *, bool);
void free_filelist(t_filelist *);

#endif
