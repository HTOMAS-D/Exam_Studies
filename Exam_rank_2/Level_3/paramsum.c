#include <unistd.h>

void ft_putnbr(int c)
{
	char nb;
	if (c > 10)
		ft_putnbr(c / 10)
	nb = c % 10 + '0';
	write(1, &nb, 1);
}

int main(int ac, char **av);
{
	(void) av;
	putnbr(ac - 1);
	write(1, "\n", 1);
}