/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	queue_to_next(t_queue *queue)
{
	t_cont *next;

	next = queue->cont->next;
	free(queue->cont);
	queue->cont = next;
}

void	del_link_by_out(t_lem *lemin, int i, t_queue queue)
{
	lemin->links[queue.cont->id][i] = 0;
	lemin->links[i][queue.cont->id] = 0;
	lemin->rooms[i].out--;
	lemin->rooms[queue.cont->id].in--;
}

void	check_out(t_lem *lemin)
{
	int		i;
	t_queue	queue;

	i = 0;
	while (i < lemin->r_count)
		lemin->rooms[i++].is_visit = 0;
	queue = init_queue(lemin->end);
	while (queue.cont != NULL)
	{
		i = -1;
		while (++i < queue.cont->id)
			if (lemin->links[queue.cont->id][i] == 1 && lemin->rooms[i].out > 1
				&& lemin->rooms[i].is_visit == 1 && i != lemin->start)
			{
				del_link_by_out(lemin, i, queue);
				break ;
			}
			else if (lemin->links[queue.cont->id][i] == 1 && i != lemin->start)
			{
				lemin->rooms[i].is_visit = 1;
				new_elem(i, &queue);
			}
		queue_to_next(&queue);
	}
}
