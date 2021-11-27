#include "minishell.h"

void	join_free(int mode, char **src, char *dst)
{
	char	*tmp;

	tmp = *src;
	(*src) = ft_strjoin(*src, dst);
	if (!(*src))
		exit(1);
	free(tmp);
	if (mode == 1)
		free(dst);
}

int	my_putchar(int c)
{
	return (write(1, &c, 1));
}

void	free_array(char **array)
{
	unsigned int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}
