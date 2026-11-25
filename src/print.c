#include "../include/filelist.h"

static void set_perm_str(mode_t, char[10]);
static char get_filetype_chr(mode_t);
static void print_username_from_uid(uid_t);
static void print_groupname_from_gid(gid_t);
static void print_mtime(time_t);

void print_filelist(const t_filelist *fl, const t_options *options) {
  // TODO: 幅の取得 文字列として取得する関数をそれぞれについて作る
  // size_t nlink_width, owner_width, group_width, file_size_width;

  for (size_t i = 0; i < fl->count; ++i) {
    const t_fileinfo *file = &fl->files[i];
    if (options->long_listing_format) {
      mode_t perm =
          file->stat.st_mode & (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO);
      char perm_str[10];
      set_perm_str(perm, perm_str);
      printf("%c%s ", get_filetype_chr(file->stat.st_mode), perm_str);
      printf("%ju ", (uintmax_t)file->stat.st_nlink);
      print_username_from_uid(file->stat.st_uid);
      print_groupname_from_gid(file->stat.st_gid);
      printf("%jd ", (intmax_t)file->stat.st_size);
      print_mtime(file->stat.st_mtime);
    }
    printf("%s", fl->files[i].name);
    if (i == fl->count - 1 || options->long_listing_format)
      printf("\n");
    else
      printf("  ");
  }
}

static void set_perm_str(mode_t perm, char str[10]) {
  bzero(str, 10);
  for (int i = 0; i < 9; ++i) {
    str[i] = '-';
  }

  if (perm & S_IRUSR)
    str[0] = 'r';
  if (perm & S_IWUSR)
    str[1] = 'w';
  if (perm & S_IXUSR)
    str[2] = 'x';

  if (perm & S_IRGRP)
    str[3] = 'r';
  if (perm & S_IWGRP)
    str[4] = 'w';
  if (perm & S_IXGRP)
    str[5] = 'x';

  if (perm & S_IROTH)
    str[6] = 'r';
  if (perm & S_IWOTH)
    str[7] = 'w';
  if (perm & S_IXOTH)
    str[8] = 'x';

  if (perm & S_ISUID)
    str[2] = (perm & S_IXUSR) ? 's' : 'S';
  if (perm & S_ISGID)
    str[5] = (perm & S_IXGRP) ? 's' : 'S';
  if (perm & S_ISVTX)
    str[8] = (perm & S_IXOTH) ? 't' : 'T';
}

static char get_filetype_chr(mode_t mode) {
  if (S_ISREG(mode))
    return '-';
  if (S_ISDIR(mode))
    return 'd';
  if (S_ISLNK(mode))
    return 'l';
  if (S_ISCHR(mode))
    return 'c';
  if (S_ISBLK(mode))
    return 'b';
  if (S_ISFIFO(mode))
    return 'p';
  if (S_ISSOCK(mode))
    return 's';

  return '?';
}

static void print_username_from_uid(uid_t uid) {
  struct passwd *pw = getpwuid(uid);
  if (pw)
    printf("%s ", pw->pw_name);
  else
    printf("%ju ", (uintmax_t)uid);
}

static void print_groupname_from_gid(gid_t gid) {
  struct group *gr = getgrgid(gid);
  if (gr)
    printf("%s ", gr->gr_name);
  else
    printf("%ju ", (uintmax_t)gid);
}

static void print_mtime(time_t mtime) {
  char buf[64];

  // TODO: 半年の判定をして表示を変える
  if (strftime(buf, sizeof(buf), "%b %e %H:%M", localtime(&mtime)) == 0)
    printf("%jd ", (intmax_t)mtime);
  else
    printf("%s ", buf);
}
