#include "lem_in.h"

int		ft_mini_atoi(char *line)
{
	unsigned	ents;
	unsigned	i;

	ents = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			ents = ents * 10 + line[i] - '0';
			++i;
		}
		else
			ft_error(); // "not valid number of ants"
	}
	i == 0 || i > 10 || ents > 2147483647 ? ft_error() : 0; // "not valid number of ants"
	free(line);
	return (ents);
}

int comments(char *str)
{
	if (str[0] == '#' && (str[1] != '#' || !str[1]))
	{
		free(str);
		str = NULL;
		return (1);
	}
	return (0);
}

void ft_error(void)
{
	ft_printf("ERROR : INCORENT NUMBER ANTS!");
	exit(1);
}

void	components(char **room, int f)
{
	unsigned i;

	i = 0;
	while (room[i] && i < 4)
		i++;
	i != 3 && f ? ft_error() : 0; // name x y
	i != 2 && !f ? ft_error() : 0; // name0-name1
}
