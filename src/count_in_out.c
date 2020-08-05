/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_in_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	delete_dead_end(t_lem *lemin, int i)
{
	int j;

	j = 0;
	if (i == lemin->end)
		return ;
	if (lemin->rooms[i].out == 0)
	{
		while (j < lemin->r_count)
		{
			if (lemin->links[i][j] == 1)
			{
				lemin->links[i][j] = 0;
				lemin->links[j][i] = 0;
				lemin->rooms[j].out--;
				lemin->rooms[i].in--;
				delete_dead_end(lemin, j);
			}
			j++;
		}
	}
}

void	balance_in_out(t_lem *lemin, int i, int j)
{
	if (lemin->rooms[i].level < lemin->rooms[j].level)
	{
		lemin->rooms[i].out++;
		lemin->rooms[j].in++;
	}
	else if (lemin->rooms[i].level > lemin->rooms[j].level)
	{
		lemin->rooms[j].out++;
		lemin->rooms[i].in++;
	}
}

void	dfs_in_out(t_lem *lemin)
{
	int i;
	int j;

	i = 0;
	while (i < lemin->r_count)
	{
		j = i;
		while (j < lemin->r_count)
		{
			if (lemin->rooms[i].level == lemin->rooms[j].level
				&& lemin->links[i][j] == 1)
			{
				lemin->links[i][j] = 0;
				lemin->links[j][i] = 0;
			}
			if (lemin->links[i][j] == 1)
				balance_in_out(lemin, i, j);
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < lemin->r_count)
		delete_dead_end(lemin, i);
}

void	count_in_out(t_lem *lemin)
{
	int i;

	i = 0;
	while (i < lemin->r_count)
	{
		lemin->rooms[i].in = 0;
		lemin->rooms[i].out = 0;
		i++;
	}
	dfs_in_out(lemin);
}
