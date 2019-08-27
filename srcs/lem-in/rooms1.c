#include "lem_in.h"

/*
* посещение уже посещенных комнат для восстановления флагов и глубины
*/

void	restore_room(t_map *map)
{
	t_list	*combination;
	t_list	*new_combination;
	t_room	*read;

	combination = bfs_inc(map->start->links, 0);
	new_combination = NULL;
	while(combination)
	{
		read = combination->content;
		if (read->f || read->gl)
		{
			read->f = 0;
			read->gl = 0;
			up_combination(&new_combination, read, 0);
		}
		combination = step(combination);
		if (!combination)
		{
			combination = new_combination;
			new_combination = NULL;
		}
	}
}

void	rooms_in_array(t_map *map, int *f)
{
	t_list *temp;
	unsigned i;

	i = 0;
	f[0] = 1;
	temp = map->first_room_create; // save *p
	if (!(map->room = ft_memalloc(sizeof(t_room *) * map->max_room + 1))) // + NULL
		exit(1);
	while (temp) // move on **room IDFKI
	{
		map->room[i] = temp->content;
		++i;
		temp = temp->next;
	}
	free(map->first_room_create); // mb leak but save content
	map->first_room_create = NULL;
	check_double_name(map);
	ft_sort_array(map);
	i = 0;
	while (i < map->max_room) // push index
	{
		map->room[i]->n = i;
		++i;
	}
}

void	check_double_name(t_map *map)
{
	unsigned i;
	unsigned j;

	i = 0;
	j = 1;
	while (i < map->max_room)
	{
		while (j < map->max_room)
		{
			if (ft_strcmp(map->room[i]->name, map->room[i + j]->name) == 0)
			{
				ft_printf("Error: double room names\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

t_room	*create_room(char **room)
{
	t_room	*create;

	if (!(create = ft_memalloc(sizeof(t_room))))
		exit(1);
	create->name = room[0];
	if (!ft_strncmp(create->name, "L", 1))
	{
		ft_printf("Error: not valid room name");
		exit(1);
	}
	create->x = ft_mini_atoi(room[1]);
	create->y = ft_mini_atoi(room[2]);
	free(room);
	room = NULL;
	return (create);
}

