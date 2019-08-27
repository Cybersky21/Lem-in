#include "lem_in.h"

void	ft_starts(t_map *map, int fd, char *str)
{
	char **room;

	room = NULL;
	map->start ? ft_error("double start") : 0; // "double start"
	while (get_next_line(fd, &str) && comments(str))
	{
	}
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error("dont have a room");
	free(str);
	map->start = create_room(room);
	++map->max_room;
	ft_lstadd(&map->first_room_create, ft_lstnew_ptr(map->start));
}

void	ft_end(t_map *map, int fd, char *str)
{
	char **room;

	room = NULL;
	map->end ? ft_error("double finish") : 0; // "double end"
	while (get_next_line(fd, &str) && comments(str))
	{
	}
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error("dont have a room");
	free(str);
	map->end = create_room(room);
	++map->max_room;
	ft_lstadd(&map->first_room_create, ft_lstnew_ptr(map->end));
}

void over_room(t_map *map, char *str)
{
	char	**room;
	t_room	*temp;

	room = NULL;
	room = ft_strsplit(str, ' ');
	room ? components(room, 1) : ft_error("dont have a room");
	free(str);
	temp = create_room(room); // room free in create_room
	++map->max_room;
	ft_lstadd(&map->first_room_create, ft_lstnew_ptr(temp));
}

int	ft_start_and_end(t_map *map, int fd, char *str)
{
	if (!ft_strcmp(str, "##start"))
	{
		free(str);
		str = NULL;
		ft_starts(map, fd, str);
		return (1);
	}
	else if(!ft_strcmp(str, "##end"))
	{
		free(str);
		str = NULL;
		ft_end(map, fd, str);
		return (1);
	}
	return (0);
}

void rooms(t_map *map, int fd)
{
	char *str;
	int f; // still rooms

	str = NULL;
	f = 0;
	while (get_next_line(fd, &str))
	{
		ft_printf("%s\n", str);
		if (comments(str))
			continue;
		else if (!f && ft_start_and_end(map, fd, str))
			continue;
		else if (!f && ft_strrchr(str, ' '))
			over_room(map, str);
		else if (!f && ft_strrchr(str, '-'))
		{
			rooms_in_array(map, &f);
			create_links(map, str);
		}
		else if (f && ft_strrchr(str, '-'))
			create_links(map, str);
		else
			ft_error("smth wrong with rooms");
	}
}

