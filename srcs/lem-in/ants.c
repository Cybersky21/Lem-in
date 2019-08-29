#include "lem_in.h"

// int     index_of_ram(t_map *map)
// {
//     //int ind;
//     int i;

//     // ind = map->ants;
//     i = 0;
//     //shlould count all ways long a-a1-a2=a
//     i = map->ants ;
//     return (i);
// }

void 	ants(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while(map->ants == 0 && get_next_line(fd, &str))
	{
		if (comments(str))
		{
			free(str);
			str = NULL;
			continue;
		}
		map->ants = ft_mini_atoi(str);
	}
}

int		lenways(t_list *tmp, int i, int ants, t_ind *index)
{
	t_list	*list;
	int		ind;
	int		was;

	was = i;
	ind = 0;
	while (was)
	{
		list = tmp->content;
		ind += ft_lstlen(list) + 2;
		ft_printf(" %d ", ind); //
		list = tmp->next;
		--was;
	}
	ind = (ind - 1 + ants) / i;
	// if (index->index_ram == 0)
	//	 index->index_ram = ind;
	if (index->index_ram == 0 || ind < index->index_ram) // i == 1
	{
		index->index_ram = ind;
		index->count_ways = i;
		index->way = tmp;
	}
	ft_printf("%d\n", index->index_ram); //
	return (ind);
}

// void	print_moves(t_map *map, int *ants, int *path_tab)
// {
// 	int i;

// 	i = 0;
// 	while (i < map->ants)
// 	{
// 		if (ants[i] > -1 && ants[i] < map->max_room)
// 			ft_printf("L%d-%s ", i + 1, map->room[i]->name); //
// 		i++;
// 	}
// }

// void	print_ant(int ant, char *room)
// {
// 	ft_putchar('L');
// 	ft_putnbr(ant);
// 	ft_putchar('-');
// 	ft_putstr(room);
// 	ft_putchar(' ');
// }