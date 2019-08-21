#include "lem_in.h"

t_room	*book_search(t_map *map, char *name, unsigned st, unsigned fin)
{
	unsigned med;

	med = (st + fin) / 2;
	if (!ft_strcmp(map->room[med]->name, name))
		return (map->room[med]);
	else if (st == fin)
		ft_error();
	else if (ft_strcmp(map->room[med]->name, name) > 0)
		return (book_search(map, name, med, fin));
	else if (ft_strcmp(map->room[med]->name, name) < 0)
		return (book_search(map, name, st, med));
	return (NULL);
}
