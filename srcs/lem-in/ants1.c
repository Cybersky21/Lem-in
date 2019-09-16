/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:33:54 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/10 15:35:12 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	**room_way_in_array(t_list *way, t_way *link)
{
	t_room		**room;
	t_list		*temp;
	unsigned	i;

	link->i = ft_lstlen(way);
	if (!(room = ft_memalloc(sizeof(t_room *) * (link->i + 1))))
		exit(1);
	temp = way;
	i = 0;
	while (temp)
	{
		room[i] = temp->content;
		++i;
		temp = temp->next;
	}
	return (room);
}

t_way	**way_transform(t_ind *ind)
{
	t_way	**all;
	t_list	*tmp_all;
	t_list	*temp_vn;
	int		way;

	way = 0;
	tmp_all = ind->all_ways;
	if (!(all = (t_way **)ft_memalloc(sizeof(t_way *) * (ind->count_ways + 1))))
		exit(1);
	all[ind->count_ways] = NULL;
	while (way < ind->count_ways)
	{
		temp_vn = tmp_all->content;
		all[way] = ft_memalloc(sizeof(t_way));
		all[way]->room = room_way_in_array(temp_vn, all[way]);
		++way;
		tmp_all = tmp_all->next;
	}
	return (all);
}

void	combo(t_list *tmp, t_ind *ind, int ants)
{
	int	len_comb;
	int	index;

	index = 1;
	len_comb = ft_lstlen(tmp);
	while (len_comb)
	{
		lenways(tmp, index++, ants, ind);
		--len_comb;
	}
}

void	unpacking(t_map *map, t_ind *ind)
{
	t_list	*tmp;
	t_list	*st;
	t_way	**all;

	st = map->combination;
	while (st)
	{
		tmp = st->content;
		combo(tmp, ind, map->ants);
		st = st->next;
	}
	all = way_transform(ind);
	print_ants_on_way(all, map->end, map->ants, ind);
	write(1, "\n", 1);
	free_array(all);
	free_map(map);
}
