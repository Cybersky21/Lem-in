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
	while (temp && gl)
	{
		read = temp->content;
		temp->content_size = 0; // блокировка направления
		if (read->gl == gl && !read->isp) // wasnt visit
		{
			ft_lstadd(&way, ft_lstnew_ptr(read));
			temp = read->links;
			read->isp = 1; // to 0 in some circumstances
			--gl;
		}
		else
			temp = temp->next;
	}
	way ? ft_lstadd(&map->first_room_create, ft_lstnew_ptr(way)) : 0;
}
