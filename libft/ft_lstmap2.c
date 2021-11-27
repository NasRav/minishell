#include "libft.h"

t_list2	*ft_lstmap2(t_list2 *lst, char *(*f)(const char *), \
		void (*del)(void *))
{
	t_list2	*newlst;
	t_list2	*lstcpy;

	lstcpy = 0;
	lst = ft_lstfirst2(lst);
	while (lst)
	{
		newlst = ft_lstnew2((*f)(lst->content));
		if (!newlst)
		{
			ft_lstclear2(&lstcpy, del);
			return (0);
		}
		lst = lst->next;
		ft_lstadd_back2(&lstcpy, newlst);
	}
	return (lstcpy);
}
