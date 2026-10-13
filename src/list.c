#include "../include/list.h"

t_list *ft_lstnew(char *filename)
{
  t_list *new;

  new = (t_list *)calloc(sizeof(t_list), 1);
  if (!new)
    return NULL;
  new->next = NULL;
  new->filename = filename;
  return new;
}

t_list *ft_lstlast(t_list *lst)
{
  while (lst)
    {
      if (lst->next == NULL)
	break ;
      lst = lst->next;
    }
  return lst;
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
  t_list *t;

  if (*lst)
    {
      t = ft_lstlast(*lst);
      t->next = &*new;
    }
  else
    *lst = new;
}

void ft_lstdelone(t_list *lst)
{
  if (!lst)
    return ;
  free(lst);
}

void ft_lstclear(t_list **lst)
{
  t_list *t;
  t_list *tmp;

  t = *lst;
  while (t)
    {
      tmp = t->next;
      ft_lstdelone(t);
      t = tmp;
    }
  *lst = NULL;
}

size_t ft_lstsize(t_list *lst)
{
  size_t i;

  i = 0;
  while (lst)
    {
      lst = lst->next;
      ++i;
    }
  return i;
}


void ft_printlst(t_list *lst)
{
  while (lst)
    {
      printf("filename: %s\n", lst->filename);
      lst = lst->next;
    }
}
