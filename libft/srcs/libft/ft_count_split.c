#include "libft.h"

int		ft_count_split(char **split)
{
	int i;

	i = 0;
	if (split == NULL)
		return (0);
	while(split[i] != NULL)
		i++;
	return (i);
}
