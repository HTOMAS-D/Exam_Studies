#include <unistd.h>


void ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
		write(1, &str[i++], 1);
}

void do_stuff(char *str, char *comp)
{
	int i = 0;
	int j = 0;

	while (comp[j])
	{
		if (str[i] == comp[j++])
			i++;
		
	}
	if (!str[i])
		ft_putstr(str);
}

int main(int ac, char **av)
{
	if (ac == 3)
		do_stuff(av[1], av[2]);
	write(1, "\n", 1);
}