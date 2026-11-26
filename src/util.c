#include "../include/util.h"

char *join_path(const char *path, const char *filename) {
  size_t path_len = strlen(path);
  while (path_len > 1 && path[path_len - 1] == '/')
    --path_len;

  char *full_path = calloc(strlen(path) + strlen(filename) + 2, sizeof(char));
  if (!full_path)
    exit(2);
  memcpy(full_path, path, path_len);
  if (path[path_len - 1] != '/')
    strcat(full_path, "/");
  strcat(full_path, filename);
  return full_path;
}
