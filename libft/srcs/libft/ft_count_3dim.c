#include "../includes/libft.h"

int		ft_count_3dim(char ***data)
{
	int i;

	i = 0;
	while (data[i])
	{
		i++;
	}
	return (i);
}