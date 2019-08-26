#include <zconf.h>
#include "lem_in.h"

void 	ants(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while(map->ants == 0 && get_next_line(fd, &str))
	{
		if (comments(str))
			continue;
		map->ants = ft_mini_atoi(str);
	}
}

void 	ft_sort_array(t_map *map)
{
	unsigned	i;
	t_room		*temp;

	i = 0;
	while (i < map->max_room - 1)
	{
		if (ft_strcmp(map->room[i]->name, map->room[i + 1]->name) > 0)
		{
			temp = map->room[i + 1];
			map->room[i + 1] = map->room[i];
			map->room[i] = temp;
			i = i > 2 ? i - 2 : 0;
		}
		else
			++i;
	}
}

t_room	*seach_room(t_room **rooms, unsigned i, unsigned j, char *name)
{
	unsigned	p;
	int			cmp;

	cmp = ft_strcmp(name, rooms[p]->name);
	p = (i + j) / 2;
	if (!cmp)
		return (rooms[p]);
	else if (i == j)
		return (NULL);
	else if (cmp > 0)
		return (seach_room(rooms, p, j, name));
	else if (cmp < 0)
		return (seach_room(rooms, i, p, name));
	return (NULL);
}

void 	create_links(t_map *map, char *str)
{
	char	**room;
	t_room	*fist;
	t_room	*second;

	room = NULL;
	fist = NULL;
	second = NULL;
	room = ft_strsplit(str, '-');
	components(room, 0);
	fist = seach_room(map->room, 0, map->max_room, room[0]);
	second = seach_room(map->room, 0, map->max_room, room[1]);
	!fist || !second ? ft_error() : 0; // "dont have first or second room"
	// if we havent got this link, we go ahead, if we have - dont
	ft_lstadd(&fist->links, ft_lstnew_ptr(second)); //
	ft_lstadd(&second->links, ft_lstnew_ptr(fist));
	// free **room
	free(str);
	str = NULL;
}

void	test_print(t_list *test)
{
	t_list *temp;
	t_room	*read;

	temp = test->content;
	while (temp)
	{
		read = temp->content;
		ft_printf("%s\n", read->name);
		temp = temp->next;
	}
}

int				main(int a, char **b)
{
	int fd;
	t_map map;

	fd = ft_read_file(b[1]); // only for debug // fd = 0
	ft_bzero(&map, sizeof(map));
	ents(&map, fd); // +
	rooms(&map, fd); // +
	while (bfs(&map))// width search 
	{
		patch(&map); // collect 1 way
		restore_room(&map);
	}
	test_print(map.first_room_create); // for debug
	return (0);
}

// поменять либу на либу с CoreWar
// для поиска комбинаций
// блокировка направлений (менять content_size) 
//
// void ? устанавливает значения по умолчанию 
// занулить ширину/глубину итд для нового поиска в глубину finish никогда не посещен
// ориентироваться по направлениям (не пересеченные ранее)
// отсекающие пути сохраняются 
// 
// int выбираем последнюю комбинацию пути - проверяем реверсно а-б-в-г г-в-б-а - удалить из links ребро в обе стороны
// восстанавливаем все, кроме этой связи и заново поиск в глубину
//
// список для посещения посещенных комнат read->f = 1; то зануляем и читаем информацию

// для муравьев
// определение шагов по путям (+ заполнение), запомнить наименьший параметр + сколько путей
//
// сколько муравьев в какую комнату пустить (в первый больше всего, дальше - меньше или столько же)
//
// печать
// free all (start && finish оставить, удалятся при удалении всех комнат)
// в глубину - чистить глубину - и их самих (free(name))->(free(links))
// NOT FREE CONTENT 
// занулять после free