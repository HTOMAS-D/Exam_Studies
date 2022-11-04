#include <stdio.h>

char *ft_strcpy(char *s1, char *s2)
{
	int i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

int main()
{
	char s1[] = "enriqueh";
	char s2[] = "henrique";
	
	printf("%s\n", ft_strcpy(s1, s2));
}