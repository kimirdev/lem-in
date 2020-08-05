/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	run_ant(t_lem lemin, int *ant, int *finished)
{
	if (*ant <= lemin.a_count)
	{
		while (lemin.paths != NULL)
		{
			if ((lemin.paths->first->ant == 0 &&
				lemin.paths->ratio < lemin.a_count - (*ant) + 1)
				|| lemin.paths->first == lemin.paths->last)
			{
				print_ant_step(ft_itoa(*ant), \
					lemin.rooms[lemin.paths->first->id].name);
				if (lemin.paths->first == lemin.paths->last)
					if (++(*finished) >= lemin.a_count)
						return ;
				lemin.paths->first->ant = *ant;
				if (++(*ant) > lemin.a_count)
					break ;
			}
			lemin.paths = lemin.paths->next;
		}
	}
	write(1, "\n", 1);
}

void	move_ant(t_lem *lemin, t_cont *curr, t_path *c_path)
{
	if (curr->ant != 0)
	{
		if (curr->next == c_path->last)
		{
			print_ant_step(ft_itoa(curr->ant), \
				lemin->rooms[curr->next->id].name);
			if (++(lemin->finished) >= lemin->a_count)
				return ;
		}
		else
		{
			print_ant_step(ft_itoa(curr->ant), \
				lemin->rooms[curr->next->id].name);
			curr->next->ant = curr->ant;
		}
		curr->ant = 0;
	}
}

void	move_possible(t_lem *lemin)
{
	t_path *c_path;
	t_cont *curr;

	c_path = lemin->paths;
	curr = c_path->last;
	while (c_path != NULL)
	{
		curr = c_path->last->prev;
		while (curr != NULL)
		{
			move_ant(lemin, curr, c_path);
			curr = curr->prev;
		}
		c_path = c_path->next;
	}
}

void	count_ratio(t_lem lemin)
{
	int i;
	int sum;

	i = 1;
	sum = lemin.paths->size;
	lemin.paths->ratio = 0;
	lemin.paths = lemin.paths->next;
	while (lemin.paths != NULL)
	{
		lemin.paths->ratio = i * lemin.paths->size - sum;
		sum += lemin.paths->size;
		i++;
		lemin.paths = lemin.paths->next;
	}
}

void	move_ants(t_lem lemin)
{
	int ant;

	ant = 1;
	lemin.finished = 0;
	count_ratio(lemin);
	while (lemin.finished < lemin.a_count)
	{
		run_ant(lemin, &ant, &(lemin.finished));
		move_possible(&lemin);
	}
	write(1, "\n", 1);
}
