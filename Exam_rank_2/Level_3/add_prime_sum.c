#include <stdlib.h>
#include <unistd.h>

int ft_atoi(char *str)
{
	int numb;
	int i = 0;
	int flag = 1;

	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	while (str[i])
	{
		numb = numb * 10  + str[i] - '0';
		i++;
	}
	return (numb * flag);
}

int check_args(char *str)
{
	int numb = ft_atoi(str);
	if (numb <= 0)
	{
		write(1, "0\n", 2);
		exit(1);
	}
	return (numb);

}

int is_prime(int nb)
{
	int i = 3;

	if (nb <= 1)
		return 0;
	if (nb % 2 == 0 && nb > 2)
		return 0;
	while(i < (nb / 2))
	{
		if (nb % i == 0)
			return 0;
		i += 2;
	}
	return i;
}

int main(int ac, char **av)
{
	
	if (ac == 2)
	{
		int numb = check_args(av[1]);
		int n = 0;
		result = 0;
		while(n < numb)
		{
			if (is_prime(numb--))
				result += numb;
			//inset putnbr here//
		}
	}
	else
	{
		write(1, "0\n", 2);
		exit(2);
	}
}