#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char *src)
{
	int i = 0;
	char *str = (char *) malloc(sizeof(char) * (ft_strlen(src) + 1));
	
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int main()
{
	char *str = "henrique";
	char *new = ft_strdup(str);
	printf("%s\n", new);
	free(new);
}