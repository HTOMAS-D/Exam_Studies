unsigned int lcm(unsigned int a, unsigned int b)
{
	unsigned int mult;
	if	(a == 0 || b == 0)
		return 0;
	if (a > b)
		mult = a;
	else
		mult = b;
	while(1)
	{
		if (mult % a == 0 && mult % b == 0)
			return (mult);
		mult++;
	}
}