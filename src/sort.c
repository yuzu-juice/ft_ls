#include "../include/sort.h"

int compare_filename(const void *a, const void *b) {
  const t_fileinfo *left = a;
  const t_fileinfo *right = b;

  return strcoll(left->name, right->name);
}

int compare_filename_reverse(const void *a, const void *b) { return compare_filename(b, a); }
