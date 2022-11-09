char *ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;
	int j = 0;

	while (s1[i])
	{
		j = 0;
		while (s2[i])
		{
			if (s1[i] == s2[j])
				return (s1 + 1);
			j++;
		}
		i++;
	}
	return (NULL);
}