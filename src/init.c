/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lem_init(t_lem *ret, int *a, int *i)
{
	ret->start = -1;
	ret->end = -1;
	ret->r_count = 0;
	ret->a_count = 0;
	*a = 0;
	*i = 0;
	ret->memory = 50;
	ret->rooms = (t_room*)malloc(sizeof(t_room) * 50);
}

void	new_elem(int id, t_queue *queue)
{
	queue->last->next = malloc(sizeof(t_cont));
	queue->last->next->id = id;
	queue->last->next->next = NULL;
	queue->last = queue->last->next;
}

t_queue	init_queue(int id)
{
	t_queue ret;

	ret.cont = malloc(sizeof(t_cont));
	ret.cont->id = id;
	ret.cont->next = NULL;
	ret.last = ret.cont;
	return (ret);
}

void	init_path(t_lem lemin, t_path **ret, t_cont **path, int i)
{
	int k;

	k = 0;
	while (k < lemin.r_count)
		lemin.rooms[k++].is_visit = 0;
	lemin.rooms[lemin.start].is_visit = 1;
	lemin.rooms[i].is_visit = 1;
	*ret = malloc(sizeof(t_path));
	*path = malloc(sizeof(t_cont));
	(*path)->id = i;
	(*path)->ant = 0;
	(*path)->next = NULL;
	(*ret)->next = NULL;
	(*path)->prev = NULL;
	(*ret)->path = (*path);
	(*ret)->first = (*path);
}

void	init_node_links(t_cont **path, int k)
{
	(*path)->next = malloc(sizeof(t_cont));
	(*path)->next->id = k;
	(*path)->next->ant = 0;
	(*path)->next->next = NULL;
	(*path)->next->prev = (*path);
	(*path) = (*path)->next;
}
