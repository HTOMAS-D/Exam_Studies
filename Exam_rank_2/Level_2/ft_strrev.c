#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strrev(char *str)
{
	char temp;
	int i = 0;
	int end = ft_strlen(str) - 1;
	while (end > i)
	{
		temp = str[i];
		str[i] = str[end];
		str[end] = temp;
		i++;
		end--;
	}
	return (str);
}

int main()
{
	char str[] = "henrique";
	printf("%s\n", ft_strrev(str));
}