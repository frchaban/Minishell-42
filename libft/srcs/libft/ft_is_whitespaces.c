#include "../../includes/libft.h"

int		ft_is_whitespaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
	|| c == '\f')
		return (1);
	return (0);
}