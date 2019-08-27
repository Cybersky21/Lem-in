#include "lem_in.h"

void	patch(t_map *map)
{
	t_list		*way;
	t_list		*temp;
	t_room		*read;
	int			gl;

	way = NULL;
	temp = map->end->links;
	gl = map->end->gl - 1;
	while (temp && gl)
	{
		read = temp->content;
		temp->content_size = 0; // блокировка направления
		if (read->gl == gl && !read->isp)
		{
			ft_lstadd(&way, ft_lstnew_ptr(read));
			temp = read->links;
			read->isp = 1;
			--gl;
		}
		else
			temp = temp->next;
	}
	way ? ft_lstpush(&map->first_room_create, ft_lstnew_ptr(way)) : 0;
}
