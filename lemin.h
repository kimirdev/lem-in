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

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"

typedef struct	s_room
{
	int			is_start;
	int			is_end;
	int			is_visit;
	char		name[128];
	int			x;
	int			y;
	int			level;
	int			out;
	int			in;
}				t_room;

typedef struct	s_lem
{
	int			start;
	int			end;
	t_room		*rooms;
	int			memory;
	int			**links;
	int			r_count; // room count
	int			a_count; // ant count
}				t_lem;

#endif
