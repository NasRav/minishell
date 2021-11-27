#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*dup_s;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dup_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup_s)
		return (0);
	while (i < len)
	{
		dup_s[i] = s[i];
		i++;
	}
	dup_s[len] = '\0';
	return (dup_s);
}
