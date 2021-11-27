#include "libft.h"

static int	trim_num(char const *s, char const *set)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (set[j] && s[i] != set[j])
			j++;
		if (!set[j])
			return (i);
		if (s[i] == set[j])
			i++;
	}
	return (i);
}

static int	trim_num_rev(char const *s, char const *set)
{
	int		i;
	int		j;
	int		len;

	len = ft_strlen(s) - 1;
	i = len;
	while (i > 0)
	{
		j = 0;
		while (set[j] && s[i] != set[j])
			j++;
		if (!set[j])
			return (len - i);
		if (s[i] == set[j])
			i--;
	}
	return (len - i);
}

static int	dest_len(const char *str, const char *set)
{
	int		s_len;

	s_len = ft_strlen(str);
	s_len -= trim_num(str, set);
	if (s_len > 0)
		s_len -= trim_num_rev(str, set);
	return (s_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		s_len;
	int		i;
	int		l;

	if (s1 == NULL || set == NULL)
		return (0);
	i = 0;
	s_len = dest_len(s1, set);
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!str)
		return (0);
	l = trim_num(s1, set);
	while (i < s_len)
	{
		str[i] = s1[l + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
