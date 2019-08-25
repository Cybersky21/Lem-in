#ifndef LEM_IN_H
# define LEM_IN_H

# include "ft_printf.h"
# include <stdio.h>
# include <limits.h>
# include <math.h>

# define SECURE_MALLOC(a)	!(a) && memory_error()

typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
	int		n; // first, second, etc
	int		f; // flag was/wasn't
	int		isp; // was used like f
	int		gl; // deep or length of road
	t_list	*links; 
	int		ant_num; // ??
}				t_room;

typedef struct	s_map
{
	int 	ants;
	t_room	**room;
	t_room	*start;
	t_room	*end;
	t_list	*first_room_create; // for begin of algorithm
	char 	*first_link; // ??
	unsigned max_room; // all
	t_list	*combination; // roads

}				t_map;


int			main(int a, char **b);

void 		ants(t_map *map, int fd);
int			comments(char *str);
int			ft_mini_atoi(char *line);
void		ft_error(void);

void		rooms(t_map *map, int fd);
int			ft_start_and_end(t_map *map, int fd, char *str);
void		ft_start(t_map *map, int fd, char *str);
void		components(char **room, int f);
t_room		*create_room(char **room);
void		ft_end(t_map *map, int fd, char *str);
void		over_room(t_map *map, char *str);
void		rooms_in_array(t_map *map, int *f);
void		check_double_name(t_map *map);
void 		ft_sort_array(t_map *map);
void 		create_links(t_map *map, char *str);
t_room		*seach_room(t_room **rooms, unsigned i, unsigned j, char *name);

int			bfs(t_map *map);
t_list		*bfs_inc(t_list *startlinks);
void		up_combination(t_list **new_combination, t_room *room);
t_list		*step(t_list *combination);


void		rooms_in_mass(t_map *map, int fd);

#endif
