#include "../include/filelist.h"

static void add_file(t_filelist *, DIR *, struct dirent *);

t_filelist init_filelist(char *path, bool all) {
  t_filelist fl = {0};

  DIR *d = opendir(path);
  if (d) {
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
      if (!all && ent->d_name[0] == '.')
        continue;
      add_file(&fl, d, ent);
    }
    closedir(d);
  } else {
    fprintf(stderr, "ft_ls: cannot access '%s': %s\n", path, strerror(errno));
  }
  return fl;
}

static void add_file(t_filelist *fl, DIR *d, struct dirent *ent) {
  t_fileinfo *tmp;
  size_t new_capacity;

  if (fl->count == fl->capacity) {
    new_capacity = fl->capacity == 0 ? 1 : fl->capacity * 2;
    tmp = realloc(fl->files, new_capacity * sizeof(*tmp));
    if (!tmp)
      exit(2);
    fl->files = tmp;
    fl->capacity = new_capacity;
  }
  t_fileinfo *current = &fl->files[fl->count];
  *current = (t_fileinfo){0};
  current->name = strdup(ent->d_name);
  if (!current->name)
    exit(2);
  // TODO: 一旦は NULL あとでシンボリックリンクは実装
  current->linkname = NULL;
  if (fstatat(dirfd(d), ent->d_name, &current->stat, AT_SYMLINK_NOFOLLOW) == -1) {
    // エラーを報告し、この項目は追加しない
    free(current->name);
    return;
  }
  ++fl->count;
}

void free_filelist(t_filelist *fl) {
  for (size_t i = 0; i < fl->count; ++i)
    free(fl->files[i].name);
  free(fl->files);
  *fl = (t_filelist){0};
}
