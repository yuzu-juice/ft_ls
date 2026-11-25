#include "../include/sort.h"

int compare_filename(const void *a, const void *b) {
  const t_fileinfo *left = a;
  const t_fileinfo *right = b;

  return strcoll(left->name, right->name);
}

int compare_timestamp(const void *a, const void *b) {
  const t_fileinfo *file_a = a;
  const t_fileinfo *file_b = b;
  const struct timespec a_time = file_a->stat.st_mtim;
  const struct timespec b_time = file_b->stat.st_mtim;

  if (a_time.tv_sec != b_time.tv_sec)
    return a_time.tv_sec < b_time.tv_sec ? 1 : -1;
  if (a_time.tv_nsec != b_time.tv_nsec)
    return a_time.tv_nsec < b_time.tv_nsec ? 1 : -1;
  return compare_filename(a, b);
}

void reverse_filelist(t_filelist *fl) {
  for (size_t i = 0; i < fl->count / 2; ++i) {
    t_fileinfo *files = fl->files;
    t_fileinfo tmp = files[i];
    files[i] = files[fl->count - i - 1];
    files[fl->count - i - 1] = tmp;
  }
}
