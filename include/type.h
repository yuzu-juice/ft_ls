#ifndef TYPE_H_
#define TYPE_H_

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

#define INITIAL_CAPACITY 4

typedef struct s_fileinfo {
  // The file name.
  char *name;

  // For symbolic link, name of the file linked to, otherwise zero.
  char *linkname;

  struct stat stat;
  /*
  // Cached screen width (including quoting).
  size_t width;
  */
} t_fileinfo;

typedef struct s_options {
  bool all;
  bool long_listing_format;
  bool reverse;
  bool recursive;
  bool sort_by_time;
} t_options;

typedef struct s_args {
  t_options options;
  char **paths;
  size_t path_count;
} t_args;

typedef struct s_filelist {
  t_fileinfo *files;
  size_t count;
  size_t capacity;
} t_filelist;

typedef struct s_stack {
  char **path;
  size_t count;
  size_t capacity;
} t_stack;

#endif
