#include <unistd.h>

void do_stuff(char *str, char s, char r)
{
	int i = 0;

	while(str[i])
	{
		if (str[i] == s)
			str[i] = r;
		write(1, &str[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if (ac == 4)
		do_stuff(av[1], av[2][0], av[3][0]);
	write(1, "\n", 1);
}