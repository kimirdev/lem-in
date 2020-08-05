/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	error_case(void *to_free)
{
	if (to_free != NULL)
		free(to_free);
	write(1, "\033[31mError\033[0m\n", 15);
	exit(0);
}

void	print_line(char *line)
{
	write(1, line, ft_strlen(line));
	write(1, "\n", 1);
}

void	print_ant_step(char *ant, char *room)
{
	int		ant_len;
	int		room_len;

	ant_len = ft_strlen(ant);
	room_len = ft_strlen(room);
	write(1, "L", 1);
	write(1, ant, ant_len);
	write(1, "-", 1);
	write(1, room, room_len);
	write(1, " ", 1);
	free(ant);
}
