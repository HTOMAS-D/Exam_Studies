#include <unistd.h>

void put_string(char *str)
{
	int i = 0;
	int j = 0;
	
	while (str[i] != '\0')
	{
		if (str[i] >= 65 && str[i] <= 90)
		{
			j = 0;
			while (j < (str[i] - 64))
			{
				write(1, &str[i], 1);
				j++;
			}
		}
		else if (str[i] >= 97 && str[i] <= 122)
		{
			j = 0;
			while (j < str[i] - 96)
			{
				write(1, &str[i], 1);
				j++;
			}
		}
		else 
			write(1, &str[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		put_string(av[1]);
	}
	write(1, "\n", 1);
	return (0);
}