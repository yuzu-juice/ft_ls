#ifndef LIST_H_
# define LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
  char *filename;
  struct s_list *next;
} t_list;

t_list *ft_lstnew(char *);
t_list *ft_lstlast(t_list *);
void ft_lstadd_back(t_list **, t_list *);
void ft_lstdelone(t_list *);
void ft_lstclear(t_list **);
size_t ft_lstsize(t_list *);
void ft_printlst(t_list *);

#endif
