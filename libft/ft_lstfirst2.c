#include "libft.h"

t_list2	*ft_lstfirst2(t_list2 *lst)
{
	t_list2	*tmp;

	tmp = lst;
	if (tmp)
	{
		while (tmp->prev)
			tmp = tmp->prev;
	}
	return (tmp);
}
