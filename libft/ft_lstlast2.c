#include "libft.h"

t_list2	*ft_lstlast2(t_list2 *lst)
{
	t_list2	*tmp;

	tmp = lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}
