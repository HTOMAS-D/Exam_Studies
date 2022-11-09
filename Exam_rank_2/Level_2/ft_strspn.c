#include <stdio.h>

int ft_strchr(const char *str, char c)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int ft_strspn(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i])
	{
		if(ft_strchr(s2, s1[i]))
			break;
		i++;
	}
	return (i);
}

int main()
{
	char str[] = "henrique";
	char str2[] ="henriqe";
	printf("%d\n", ft_strspn(str, str2));
}