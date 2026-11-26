#include "../include/stack.h"

#include <stdlib.h>
#include <string.h>

char *stack_pop(t_stack *stack) {
  if (stack->count == 0)
    return NULL;
  --stack->count;
  return stack->path[stack->count];
}

void stack_push(t_stack *stack, const char *path) {
  if (stack->count == stack->capacity) {
    size_t new_capacity = stack->capacity == 0 ? INITIAL_CAPACITY : stack->capacity * 2;
    char **tmp = realloc(stack->path, new_capacity * sizeof(*tmp));
    if (!tmp)
      exit(2);
    stack->path = tmp;
    stack->capacity = new_capacity;
  }

  stack->path[stack->count] = strdup(path);
  if (!stack->path[stack->count])
    exit(2);
  ++stack->count;
}

void stack_free(t_stack *stack) {
  for (size_t i = 0; i < stack->count; ++i)
    free(stack->path[i]);
  free(stack->path);
  *stack = (t_stack){0};
}
