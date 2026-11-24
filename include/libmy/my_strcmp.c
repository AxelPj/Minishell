int	my_strcmp(char *s, char *s2)
{
	int	i;

	i = 0;
	while (s[i] && s2[i])
	{
		if (s[i] != s2[i])
			return (s[i] - s2[i]);
		i++;
	}
	return ((unsigned char)s[i] - (unsigned char)s2[i]);
}
