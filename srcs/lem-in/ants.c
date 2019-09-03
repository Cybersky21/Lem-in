#include "lem_in.h"

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

int			check_zero(t_list *list)
{
	t_list	*tmp;
	t_room	*room;

	tmp = list;
	if (!tmp)
		return (0);
	room = tmp->content;
	while (tmp && room->ant_num == 0)
	{
		room = tmp->content;
		tmp = tmp->next;
	}
	while (tmp && room->ant_num)
	{
		room = tmp->content;
		tmp = tmp->next;
	}
	return (tmp ? 1 : 0);
}

void		print_ants(t_list *list, t_room *finish)
{
	t_room	*room;
	t_room	*up;
	t_list	*tmp;

	tmp = list;
	room = tmp->content;
	while (tmp && !room->ant_num)
	{
		room = tmp->content;
		tmp = tmp->next;
	}
	if (tmp && tmp->next)
	{
		up = tmp->next->content;
		up->ant_num = room->ant_num;
		ft_printf("L%d-%s ", up->ant_num, up->name);
		room->ant_num = 0;
	}
	else if (room->ant_num)
	{
		++finish->ant_num;
		ft_printf("L%d-%s", room->ant_num, finish->name);
	}
}

void	par_rooms(t_room *finish, t_list **list, int ants)
{
	t_room	*room;
	// t_list	*tmp;
	int		ant_i;
	int		i;
	int 	j;
	int		k;
	
	ant_i = 1;
	while (finish->ant_num != ants)
	{
		k = 0;
		while (!check_zero(list[k]))
		{
			i = 0;
			while (list[i])
			{
				print_ants(list[i], finish);
				++i;
			}
			++k;
		}
		j = 0;
		while (list[j]) // not like this
		{
			room = list[j]->content;
			room->ant_num = ant_i;
			++j;
			++ant_i;
		}
	}
}

t_list	**recharge(t_ind *ind)
{
	t_list	**list;
	t_list	*tmp;
	t_list	*cont;

	if (!(list = ft_memalloc(sizeof(t_list *) * (ind->count_ways + 1))))
		exit(1);
	tmp = ind->all_ways;
	while (ind->count_ways)
	{
		cont = tmp->content;
		list[--ind->count_ways] = cont;
		tmp = tmp->next;
	}
	return (list);
}

int		len_ant_way(t_list **list, int i, int ants)
{
	int		len;
	int		was;
	int		j;

	was = i;
	len = 0;
	j = 0;
	while (j != i)
	{
		len += ft_lstlen(list[j]) + 2;
		++j;
	}
	return ((len - 1 + ants) / was);
}

int		lenways1(t_list *tmp, int i, int ants)
{
	t_list	*list;
	int		len;
	int		was;

	was = i;
	len = 0;
	while (i)
	{
		list = tmp->content;
		len += ft_lstlen(list) + 2;
		list = tmp->next;
		--i;
	}
	return ((len - 1 + ants) / was);
}

void	lenways(t_list *tmp, int i, int ants, t_ind *index, t_list *temp_save)
{
	int		ind;

	ind = lenways1(tmp, i, ants);
	if (index->index_ram == 0 || ind < index->index_ram) // i == 1
	{
		index->index_ram = ind;
		index->count_ways = i;
		index->all_ways = temp_save;
	}
	// ft_printf("%d\n", index->index_ram); //
}
