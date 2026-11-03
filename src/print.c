#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include "../include/type.h"

static void set_perm_str(mode_t, char[10]);
static char get_filetype_chr(struct stat);

void print_fileinfo(struct dirent ent, t_args args) {
  (void)args;

  struct stat st;
  if (lstat(ent.d_name, &st) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }

  mode_t perm = st.st_mode & (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO);
  if (args.long_listing_format) {
    char perm_str[10];
    set_perm_str(perm, perm_str);
    dprintf(STDOUT_FILENO, "%s %s", perm_str, ent.d_name);
  }
  else {
    dprintf(STDOUT_FILENO, "%s", ent.d_name);
  }
}

static void set_perm_str(mode_t perm, char str[10]) {
  bzero(str, 10);
  for (int i = 0; i < 9; ++i) {
    str[i] = '-';
  }

  if (perm & S_IRUSR) str[0] = 'r';
  if (perm & S_IWUSR) str[1] = 'w';
  if (perm & S_IXUSR) str[2] = 'x';

  if (perm & S_IRGRP) str[3] = 'r';
  if (perm & S_IWGRP) str[4] = 'w';
  if (perm & S_IXGRP) str[5] = 'x';

  if (perm & S_IROTH) str[6] = 'r';
  if (perm & S_IWOTH) str[7] = 'w';
  if (perm & S_IXOTH) str[8] = 'x';

  if (perm & S_ISUID)
    str[2] = (perm & S_IXUSR) ? 's' : 'S';
  if (perm & S_ISGID)
    str[5] = (perm & S_IXGRP) ? 's' : 'S';
  if (perm & S_ISVTX)
    str[8] = (perm & S_IXOTH) ? 't' : 'T';
}

static char get_filetype_chr(struct stat st) {
  
};
