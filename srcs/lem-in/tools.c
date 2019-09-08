/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 17:49:24 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/08 21:33:17 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// for bfc
// функция очищает остатки текущей комбинации и то что успело создаться для новой

void	last_free(t_list *combination, t_list *new_combination)
{
	ft_lstdel(&combination, NULL);
	ft_lstdel(&new_combination, NULL);
}

int		ft_mini_atoi(char *line)
{
	unsigned	ants;
	unsigned	i;

	ants = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			ants = ants * 10 + line[i] - '0';
			++i;
		}
		else
			ft_error("not valid number of ants");
	}
	i == 0 || i > 10 || ants > 2147483647 ? ft_error("not valid number") : 0;
	free(line);
	return (ants);
}

int		comments(char *str)
{
	if (str[0] == '#' && (str[1] != '#' || !str[1]))
	{
		free(str);
		str = NULL;
		return (1);
	}
	return (0);
}

void 	ft_error(char *str)
{
	ft_printf("ERROR: %s\n", str);
	exit(1);
}

void	components(char **room, int f)
{
	unsigned i;

	i = 0;
	while (room[i])
		i++;
	i != 3 && f ? ft_error("not all coordinats") : 0;
	i != 2 && !f ? ft_error("only one room") : 0;
}

void	ft_clean_strstr(char **str)
{
	size_t i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	if (str)
		free(str);
}


void	free_wayind(t_way *way, t_ind *ind)
{
	int i;

	i = 0;
	ft_lstdel(&ind->all_ways, NULL);
	ind->all_ways = NULL;
	while (i < way->i - 1)
	{
		ft_lstdel(&way->room[i]->links, NULL);
		free(way->room[i]->name);
		way->room[i]->name = NULL;
		free(way->room[i]);
		way->room[i] = NULL;
		++i;
	}
}

void	free_save(t_list **save)
{
	t_list *temp;
	t_list *next;
	t_list *now;

	temp = *save;
	while (temp)
	{
		now = temp->content;
		ft_lstdel((t_list **)&now, NULL);
		next = temp->next;
		free(temp);
		temp = next;
	}
	*save = NULL;
}

void	free_way(t_list **way)
{
	t_list *temp;
	t_list *save;
	t_list *next;

	if (*way == NULL)
		return ;
	temp = *way;
	while (temp)
	{
		save = temp->content;
		free_save(&save);
		next = temp->next;
		free(temp);
		temp = NULL;
		temp = next;
	}
	*way = NULL;
}

void	free_map(t_map *map)
{
	unsigned i;

	i = 0;
	while (i < map->max_room - 1)
	{
		ft_lstdel(&map->room[i]->links, NULL);
		free(map->room[i]->name);
		map->room[i]->name = NULL;
		free(map->room[i]);
		map->room[i] = NULL;
		++i;
	}
	// free(map->max_room);
	// map->max_room = NULL;
	ft_lstdel(&map->first_room_create, NULL);
	map->first_room_create = NULL;
	free(map->first_link);
	map->first_link = NULL;
	free_way(&map->combination);
}
