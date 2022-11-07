#include <unistd.h>

void do_stuff(char *str)
{
	int i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'm') || (str[i] >= 'A' && str[i] <= 'M'))
			str[i] += 13;
		else if ((str[i] >= 'n' && str[i] <= 'z') || (str[i] >= 'N' && str[i] <= 'Z'))
			str[i] -= 13;
		write (1, &str[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		do_stuff(av[1]);
	}
	write(1, "\n", 1);
}