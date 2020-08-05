/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path	*create_path(int i, t_lem lemin)
{
	t_path	*ret;
	t_cont	*path;
	int		k;

	init_path(lemin, &ret, &path, i);
	while (path->id != lemin.end)
	{
		k = 0;
		while (1)
		{
			if (lemin.links[i][k] == 1 && lemin.rooms[k].is_visit == 0)
			{
				init_node_links(&path, k);
				ret->size++;
				lemin.rooms[k].is_visit = 1;
				i = k;
				break ;
			}
			k++;
		}
	}
	ret->last = path;
	return (ret);
}

void	find_pos(t_path *ret, t_path *cur)
{
	t_path *buf;
	t_path *tmp;

	buf = ret;
	while (buf->next != NULL)
	{
		if (cur->size >= buf->size && cur->size <= buf->next->size)
		{
			tmp = buf->next;
			buf->next = cur;
			cur->next = tmp;
			break ;
		}
		buf = buf->next;
	}
}

void	first_three_paths(t_path **last, t_path **ret, t_path *cur)
{
	if (*ret == NULL)
	{
		*ret = cur;
		*last = cur;
	}
	else if (cur->size <= (*ret)->size)
	{
		cur->next = *ret;
		*ret = cur;
	}
	else if (cur->size >= (*last)->size)
	{
		(*last)->next = cur;
		*last = (*last)->next;
	}
}

t_path	*get_paths(t_lem lemin)
{
	t_path	*last;
	t_path	*ret;
	t_path	*cur;
	int		i;

	ret = NULL;
	i = 0;
	while (i < lemin.r_count)
	{
		if (lemin.links[lemin.start][i] == 1)
		{
			cur = create_path(i, lemin);
			if (ret == NULL || cur->size <= ret->size ||
				cur->size >= last->size)
				first_three_paths(&last, &ret, cur);
			else
				find_pos(ret, cur);
		}
		i++;
	}
	return (ret);
}
