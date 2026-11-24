#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <pwd.h>
#include <stdint.h>
#include "../include/print.h"
#include "../include/type.h"

static void set_perm_str(mode_t, char[10]);
static char get_filetype_chr(mode_t);
static void print_username_from_uid(uid_t);

void print_fileinfo(struct dirent ent, t_args args) {
  struct stat st;
  if (lstat(ent.d_name, &st) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }

  mode_t perm = st.st_mode & (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO);
  if (args.options.long_listing_format) {
    char perm_str[10];
    set_perm_str(perm, perm_str);
    printf("%c%s ", get_filetype_chr(st.st_mode), perm_str);
    printf("%ju ", (uintmax_t)st.st_nlink);
    print_username_from_uid(st.st_uid);
    printf("%s ", ent.d_name);
  }
  else {
    printf("%s", ent.d_name);
  }
  fflush(stdout);
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

static char get_filetype_chr(mode_t mode) {
  if (S_ISREG(mode))  return '-';
  if (S_ISDIR(mode))  return 'd';
  if (S_ISLNK(mode))  return 'l';
  if (S_ISCHR(mode))  return 'c';
  if (S_ISBLK(mode))  return 'b';
  if (S_ISFIFO(mode)) return 'p';
  if (S_ISSOCK(mode)) return 's';
  
  return '?';
}

static void print_username_from_uid(uid_t uid) {
  struct passwd *pw = getpwuid(uid);
  if (pw) {
    printf("%s ", pw->pw_name);
  } else {
    printf("%ju ", (uintmax_t)uid);
  }
}
