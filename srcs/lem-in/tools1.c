/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:31:32 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/10 15:33:18 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_clean_strstr(char **str)
{
	unsigned i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		++i;
	}
	free(str);
	str = NULL;
}

void	free_array(t_way **all)
{
	unsigned i;

	i = 0;
	while (all[i])
	{
		free(all[i]->room);
		all[i]->room = NULL;
		free(all[i]);
		++i;
	}
	free(all);
}

void	free_way(t_list *combo)
{
	t_list	*next;
	t_list	*vn;

	next = combo->next;
	while (combo)
	{
		vn = combo->content;
		ft_lstdel(&vn, NULL);
		free(combo);
		combo = next;
		if (combo)
			next = combo->next;
	}
}

void	free_combination(t_list *combo)
{
	t_list *next;
	t_list *way_combo;

	next = combo->next;
	while (combo)
	{
		way_combo = combo->content;
		free_way(way_combo);
		free(combo);
		combo = next;
	}
}

void	free_map(t_map *map)
{
	unsigned i;

	i = 0;
	free_combination(map->combination);
	while (map->room[i])
	{
		free(map->room[i]->name);
		ft_lstdel(&map->room[i]->links, NULL);
		free(map->room[i]);
		map->room[i] = NULL;
		++i;
	}
	free(map->room);
	map->room = NULL;
}
