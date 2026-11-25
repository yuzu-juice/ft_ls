#ifndef TYPE_H_
#define TYPE_H_

#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

/*
enum e_filetype
  {
    unknown,
    fifo,
    chardev,
    directory,
    blockdev,
    normal,
    symbolic_link,
    sock,
    whiteout,
    arg_directory
  };

enum e_acl_type
  {
    ACL_T_NONE,
    ACL_T_UNKNOWN,
    ACL_T_LSM_CONTEXT_ONLY,
    ACL_T_YES
  };
*/

typedef struct s_fileinfo {
  // The file name.
  char *name;

  // For symbolic link, name of the file linked to, otherwise zero.
  char *linkname;

  struct stat stat;

  /*
  // For terminal hyperlinks.
  char *absolute_name;


  enum e_filetype filetype;

  // For symbolic link and long listing, st_mode of file linked to, otherwise
zero. mode_t linkmode;

  // Security context.
  char *scontext;

  bool stat_ok;

  // For symbolic link and color printing, true if linked-to file exists,
otherwise false. bool linkok;

  // For long listings, true if the file has an access control list, or a
security context. enum e_acl_type acl_type;

  // For color listings, true if a regular file has capability info.
  bool has_capability;

  // Whether file name needs quoting. tri-state with -1 == unknown.
  int quoted;

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

#endif
