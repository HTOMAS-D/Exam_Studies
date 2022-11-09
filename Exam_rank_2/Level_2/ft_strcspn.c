#include <stdlib.h>

size_t ft_strcspn(const char *str, const char *reject)
{
	int i = 0;
	int j = 0;

	while (str[i])
	{
		j = 0;
		while (str[j])
		{
			if (str[i] == str[j])
				return (i);
			j++;
		}
		i++;
	}
	i = 0;
	while(s[i])
		i++;
	return (i);
}