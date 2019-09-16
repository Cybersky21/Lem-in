/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:18:28 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/10 15:35:10 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ants(t_map *map, int fd)
{
	char *str;

	str = NULL;
	while (map->ants == 0 && get_next_line(fd, &str))
	{
		ft_printf("%s\n", str);
		if (comments(str))
			continue;
		map->ants = ft_mini_atoi(str);
	}
}

int		lenways1(t_list *lst, int i, int ants)
{
	t_list	*tmp;
	int		len;
	int		was;
	t_list	*list;

	was = i;
	len = 0;
	tmp = lst;
	while (i)
	{
		list = tmp->content;
		len += ft_lstlen(list) + 2;
		tmp = tmp->next;
		--i;
	}
	return ((len - 1 + ants) / was);
}

void	lenways(t_list *tmp, int i, int ants, t_ind *index)
{
	int		ind;

	ind = lenways1(tmp, i, ants);
	if (index->index_ram == 0 || ind < index->index_ram)
	{
		index->index_ram = ind;
		index->count_ways = i;
		index->all_ways = tmp;
	}
}

void	print_ants_on_one_way(t_way *way, t_room *finish)
{
	int		len;
	t_room	**room;

	room = way->room;
	len = way->i - 1;
	while (len > -1)
	{
		if (room[len + 1] && room[len]->ant_num)
		{
			room[len + 1]->ant_num = room[len]->ant_num;
			ft_printf("L%d-%s ", room[len + 1]->ant_num, room[len + 1]->name);
			room[len]->ant_num = 0;
		}
		else if (!room[len + 1] && room[len]->ant_num)
		{
			++finish->ant_num;
			ft_printf("L%d-%s ", room[len]->ant_num, finish->name);
			room[len]->ant_num = 0;
		}
		--len;
	}
}

void	print_ants_on_way(t_way **r, t_room *finish, int ants, t_ind *ind)
{
	int		a;
	int		i;

	a = 1;
	while (finish->ant_num != ants)
	{
		i = 0;
		ft_putchar('\n');
		while (r[i])
		{
			print_ants_on_one_way(r[i], finish);
			++i;
		}
		i = 0;
		combo(ind->all_ways, ind, ants - a + 1);
		while (a <= ants && i < ind->count_ways)
		{
			r[i]->room[0]->ant_num = a;
			ft_printf("L%d-%s ", r[i]->room[0]->ant_num, r[i]->room[0]->name);
			++i;
			++a;
		}
	}
}
