#include "../include/sort.h"

static int compare_mtime(const struct timespec *, const struct timespec *);

static const char *path_from_qsort_item(const void *item) {
  char *const *path = item;

  return *path;
}

int compare_path(const void *a, const void *b) {
  return strcoll(path_from_qsort_item(a), path_from_qsort_item(b));
}

int compare_path_timestamp(const void *a, const void *b) {
  const char *path_a = path_from_qsort_item(a);
  const char *path_b = path_from_qsort_item(b);
  struct stat stat_a;
  struct stat stat_b;
  int stat_a_result = stat(path_a, &stat_a);
  int stat_b_result = stat(path_b, &stat_b);

  if (stat_a_result != 0) {
    if (stat_b_result != 0)
      return compare_path(a, b);
    return 1;
  }
  if (stat_b_result != 0)
    return -1;

  int mtime_order = compare_mtime(&stat_a.st_mtim, &stat_b.st_mtim);
  if (mtime_order != 0)
    return mtime_order;
  return compare_path(a, b);
}

int compare_filename(const void *a, const void *b) {
  const t_fileinfo *left = a;
  const t_fileinfo *right = b;

  return strcoll(left->name, right->name);
}

int compare_timestamp(const void *a, const void *b) {
  const t_fileinfo *file_a = a;
  const t_fileinfo *file_b = b;
  int mtime_order = compare_mtime(&file_a->stat.st_mtim, &file_b->stat.st_mtim);

  if (mtime_order != 0)
    return mtime_order;
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

void reverse_paths(char **paths, size_t count) {
  for (size_t i = 0; i < count / 2; ++i) {
    char *tmp = paths[i];
    paths[i] = paths[count - i - 1];
    paths[count - i - 1] = tmp;
  }
}

static int compare_mtime(const struct timespec *a, const struct timespec *b) {
  if (a->tv_sec > b->tv_sec)
    return -1;
  if (a->tv_sec < b->tv_sec)
    return 1;
  if (a->tv_nsec > b->tv_nsec)
    return -1;
  if (a->tv_nsec < b->tv_nsec)
    return 1;
  return 0;
}
