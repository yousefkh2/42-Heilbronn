#include <stdlib.h>
#include "libft.h"


void ft_lstclear(t_list **lst, void (*del)(void *))
{
	while (*lst && lst->next)
	{
		del(lst->content);
		*lst = lst->next;
	}
}