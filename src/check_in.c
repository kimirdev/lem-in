/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	edit_links(t_lem *lemin, int pos, int room)
{
	int i;

	i = 0;
	while (i != lemin->r_count)
	{
		if (lemin->links[pos][i] == 1 && i != room &&
			lemin->rooms[pos].level > lemin->rooms[i].level && i != lemin->end)
		{
			lemin->links[pos][i] = 0;
			lemin->links[i][pos] = 0;
			lemin->rooms[i].out--;
			lemin->rooms[pos].in--;
		}
		i++;
	}
}

void	delete_in(t_lem *lemin, int pos)
{
	int max;
	int room;
	int i;

	i = 0;
	max = 2147483647;
	while (i != lemin->r_count)
	{
		if (lemin->links[pos][i] == 1 &&
			lemin->rooms[pos].level > lemin->rooms[i].level &&
			max > lemin->rooms[i].out && i != lemin->end)
		{
			max = lemin->rooms[i].out;
			room = i;
		}
		i++;
	}
	edit_links(lemin, pos, room);
}

void	check_in(t_lem *lemin)
{
	int i;

	i = 0;
	while (i != lemin->r_count)
	{
		if (lemin->rooms[i].in > 1 && i != lemin->end)
			delete_in(lemin, i);
		i++;
	}
}
