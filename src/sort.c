#include "../include/sort.h"

int compare_filename(const void *a, const void *b) {
  const t_fileinfo *left = a;
  const t_fileinfo *right = b;

  return strcoll(left->name, right->name);
}
