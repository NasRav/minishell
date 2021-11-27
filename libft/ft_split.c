#include "libft.h"

static int	str_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		++s;
		++len;
	}
	return (len);
}

static int	words_num(const char **s, char c)
{
	int		num;
	char	*tmp;

	num = 0;
	while (**s && **s == c)
		++(*s);
	tmp = *(char **)s;
	while (*tmp)
	{
		while (*tmp && *tmp != c)
			++tmp;
		++num;
		while (*tmp && *tmp == c)
			++tmp;
	}
	return (num);
}

static void	next_word(char const **s, char c)
{
	*s = ft_strchr(*s, c);
	while (*s && **s && **s == c)
		++(*s);
}

static char	**free_arr(char **arr, int index)
{
	while (index > 0)
	{
		--index;
		free(arr[index]);
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	words = words_num(&s, c);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (arr)
	{
		i = 0;
		while (i < words)
		{
			arr[i] = (char *)malloc((str_len(s, c) + 1) * sizeof(char));
			if (arr[i])
				ft_strlcpy(arr[i], s, str_len(s, c) + 1);
			else
				return (free_arr(arr, i));
			next_word(&s, c);
			++i;
		}
		arr[i] = NULL;
	}
	return (arr);
}
