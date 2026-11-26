#ifndef SORT_H_
#define SORT_H_

#include "type.h"

#include <string.h>

int compare_path(const void *, const void *);
int compare_path_timestamp(const void *, const void *);
int compare_filename(const void *, const void *);
int compare_timestamp(const void *, const void *);
void reverse_filelist(t_filelist *);
void reverse_paths(char **, size_t);

#endif
