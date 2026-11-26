#ifndef STACK_H_
#define STACK_H_

#include "type.h"

char *stack_pop(t_stack *);
void stack_push(t_stack *, const char *);
void stack_free(t_stack *);

#endif
