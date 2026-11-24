#include "libmy.h"

void	*my_calloc(int nmemb, int size)
{
	void	*tab;
	size_t	total_size;

	total_size = (size_t)nmemb * size;
	if (total_size == 0)
		return (NULL);
	tab = malloc(total_size);
	if (!tab)
		return (NULL);
	my_memset(tab, 0, total_size);
	return (tab);
}
