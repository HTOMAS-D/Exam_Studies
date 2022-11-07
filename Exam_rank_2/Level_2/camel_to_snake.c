#include <unistd.h>
#include <stdio.h>

void do_stuff(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			write(1, "_", 1);
			str[i] = str[i] + 32;
		}
		write(1, &str[i], 1);
		i++;
	}
}

int main(int ac, char **av)
{
	if(ac == 2)
	 	do_stuff(av[1]);
	write(1, "\n", 1);
}