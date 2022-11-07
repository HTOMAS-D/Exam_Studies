#include <unistd.h>

void do_stuff(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = 122 - str[i] + 97;
		else if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = 90 - str[i] + 65;
		write(1, &str[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
		do_stuff(av[1]);
	write(1, "\n", 1);
}