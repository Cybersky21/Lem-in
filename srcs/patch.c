#include "lem_in.h"

void	patch(t_map *map)
{
	t_list	*way;
	t_list	*temp;
	t_room	*read;
	unsigned 	gl;

	way = NULL;
	temp = map->end->links;
	gl = map->end->gl - 1; // -finish
	while (temp && gl > -1)
	{
		read = temp->content;
		if (read->gl == gl) // wasnt visit
		{
			ft_lstadd(&way, ft_lstnew_ptr(read));
			temp = read->links;
			read->isp = 1; // to 0 in some circumstances
			// block direction
			--gl;
		}
		else
			temp = temp->next;
	}
	way ? ft_lstadd(&map->first_room_create, ft_lstnew_ptr(way)) : 0;
}
