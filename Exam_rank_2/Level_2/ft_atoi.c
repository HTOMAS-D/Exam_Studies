#include <stdio.h>

int ft_atoi(const char *str)
{
	int result;
	int flag = 1;
	int i = 0;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * flag);
}
int main()
{
	printf("%d\n", ft_atoi("123"));
}