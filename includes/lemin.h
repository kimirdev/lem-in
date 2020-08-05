/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:31:05 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:13 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct		s_cont
{
	int				id;
	int				ant;
	struct s_cont	*next;
	struct s_cont	*prev;
}					t_cont;

typedef struct		s_queue
{
	t_cont			*cont;
	t_cont			*last;
}					t_queue;

typedef struct		s_path
{
	int				size;
	int				ratio;
	t_cont			*path;
	t_cont			*first;
	t_cont			*last;
	struct s_path	*next;
}					t_path;

typedef struct		s_room
{
	int				is_start;
	int				is_end;
	int				is_visit;
	char			name[128];
	int				x;
	int				y;
	int				level;
	int				out;
	int				in;
	int				ant;
}					t_room;

typedef struct		s_lem
{
	int				start;
	int				end;
	t_room			*rooms;
	int				memory;
	int				**links;
	int				r_count;
	int				a_count;
	t_path			*paths;
	int				finished;
}					t_lem;

typedef	struct		s_arr
{
	int				*array;
	int				len;
}					t_arr;

typedef struct		s_c
{
	int				i;
	int				j;
	int				k;
	int				z;
	int				check;
	int				count;
}					t_c;

int					*create_first_array(t_lem *lemin, int *len);
int					*create_array(int *array, t_lem *lemin, \
					int len, int *len_new);
t_lem				validate(void);
void				count_in_out(t_lem *lemin);
void				check_in(t_lem *lemin);
void				check_out(t_lem *lemin);
void				delete_dead_end(t_lem *lemin, int i);
t_path				*get_paths(t_lem lemin);
void				move_ants(t_lem lemin);
void				free_paths(t_path *paths);
void				free_all(t_lem lemin);
void				print_line(char *line);
void				error_case(void *to_free);
t_queue				init_queue(int id);
void				new_elem(int id, t_queue *queue);
void				free_split(char **split);
int					check_comment(char *line, t_lem *ret, int *is_soe);
void				init_node_links(t_cont **path, int k);
void				init_path(t_lem lemin, t_path **ret, t_cont **path, int i);
void				ant_count(char *line, t_lem *ret);
t_lem				array_links(t_lem ret, int is_soe, int ans, char *line);
void				lem_init(t_lem *ret, int *a, int *i);
void				coords_free_and_error(t_lem *ret, char **split, char *line);
void				print_ant_step(char *ant, char *room);

#endif
