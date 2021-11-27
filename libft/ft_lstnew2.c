#include "libft.h"

t_list2	*ft_lstnew2(void *content)
{
	t_list2	*tmp;

	tmp = (t_list2 *)malloc(sizeof(t_list2));
	if (tmp)
	{
		tmp->content = content;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return (tmp);
}
