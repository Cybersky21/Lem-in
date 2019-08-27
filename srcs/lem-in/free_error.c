#include "lem_in.h"

void	ft_clean_strstr(char **str)
{
	size_t i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	if (str)
		free(str);
}

void 	ft_error(char *str)
{
	ft_printf("ERROR: %s\n", str);
	exit(1);
}
