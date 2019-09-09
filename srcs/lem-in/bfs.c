/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrooks <acrooks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:43:18 by acrooks           #+#    #+#             */
/*   Updated: 2019/09/09 21:52:30 by acrooks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*bfs_inc(t_list *startlinks, int f)
{
	t_room	*read;
	t_list	*combination;

	combination = NULL;
	while (startlinks)
	{
		read = startlinks->content;
		f && startlinks->content_size && !read->isp && !read->f ?
		ft_lstadd(&combination, ft_lstnew_ptr(read)) : 0;
		!f ? ft_lstadd(&combination, ft_lstnew_ptr(read)) : 0;
		startlinks = startlinks->next;
	}
	return (combination);
}

t_list	*step(t_list *combination)
{
	t_list *next;

	next = NULL;
	if (combination)
	{
		next = combination->next;
		free(combination);
		combination = NULL;
	}
	return (next);
}

void	up_combination(t_list **new_combination, t_room *room, int f)
{
	t_room	*read;
	t_list	*links;

	links = room->links;
	while (links)
	{
		read = links->content;
		f && !read->f && !read->isp ?
		ft_lstadd(new_combination, ft_lstnew_ptr(read)) : 0;
		!f && read->f ? ft_lstadd(new_combination, ft_lstnew_ptr(read)) : 0;
		links = links->next;
	}
}

// int		bfc1(t_map *map, t_list *combination, t_list *new_combination, unsigned gl)
// {
	
// }

int		bfs(t_map *map)
{
	t_list		*combination;
	t_list		*new_combination;
	t_room		*read;
	unsigned	gl;

	gl = 1;
	combination = bfs_inc(map->start->links, 1);
	new_combination = NULL;
	map->start->f = 1;
	while (combination)
	{
		read = combination->content;
		!read->f && !read->isp ? read->gl = gl : 0;
		read->f = 1;
		if (read->n == map->end->n)
		{
			last_free(combination, new_combination);
			return (1);
		}
		up_combination(&new_combination, read, 1);
		combination = step(combination);
		if (!combination)
		{
			combination = new_combination;
			new_combination = NULL;
			++gl;
		}
	}
	return (0);
}
