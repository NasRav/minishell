#include "libft.h"

void	ft_lstclear2(t_list2 **lst, void (*del)(void *))
{
	t_list2	*tmp;

	if (!*lst)
		*lst = NULL;
	else
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			del(tmp->content);
			free(tmp);
		}
	}
}
