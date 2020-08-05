/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_and_count_room(t_lem *lemin, int *count_entrance, int *j)
{
	int	i;

	*j = 0;
	*count_entrance = 0;
	i = 0;
	while (i < lemin->r_count)
	{
		if (lemin->links[lemin->start][i] == 1 && i != lemin->start)
		{
			if (i != lemin->end)
			{
				(*count_entrance)++;
			}
		}
		i++;
	}
}

int		*create_first_array(t_lem *lemin, int *len)
{
	int		i;
	int		count_entrance;
	int		*array_1;
	int		j;

	init_and_count_room(lemin, &count_entrance, &j);
	array_1 = (int*)malloc(sizeof(int) * (count_entrance));
	*len = count_entrance;
	i = 0;
	while (i < lemin->r_count)
	{
		if (lemin->links[lemin->start][i] == 1 && i != lemin->start)
		{
			if (i != lemin->end)
			{
				array_1[j] = i;
				lemin->rooms[i].level = lemin->rooms[lemin->start].level + 1;
				j++;
			}
		}
		i++;
	}
	return (array_1);
}

void	init_and_sum_room(t_c *var, t_lem *lemin, int *array, int len)
{
	int i;

	while (var->j < len)
	{
		i = 0;
		while (i < lemin->r_count)
		{
			if (lemin->links[array[var->j]][i] == 1)
			{
				if (lemin->rooms[i].level > lemin->rooms[array[var->j]].level \
					+ 1 && i != lemin->end)
					lemin->rooms[i].level = lemin->rooms[array[var->j]].level \
					+ 1;
				else if (i != lemin->end && lemin->rooms[i].level == -1)
				{
					lemin->rooms[i].level = lemin->rooms[array[var->j]].level \
					+ 1;
					var->count++;
				}
			}
			i++;
		}
		var->j++;
	}
}

void	add_room_in_array(t_lem *lemin, int *array, t_c *var, int **new_array)
{
	int i;

	i = 0;
	while (i < lemin->r_count)
	{
		if (lemin->links[array[var->j]][i] == 1 &&
		lemin->rooms[i].level > lemin->rooms[array[var->j]].level
		&& i != lemin->end)
		{
			var->z = 0;
			var->check = 0;
			while (var->z != var->k)
			{
				if (i == (*new_array)[var->z])
					var->check = 1;
				var->z++;
			}
			if (var->check == 0)
			{
				(*new_array)[var->k] = i;
				var->k++;
			}
		}
		i++;
	}
}

int		*create_array(int *array, t_lem *lemin, int len, int *len_new)
{
	int *new_array;
	t_c var;

	var.z = 0;
	var.check = 0;
	var.k = 0;
	var.j = 0;
	var.count = 0;
	init_and_sum_room(&var, lemin, array, len);
	*len_new = var.count;
	if (var.count == 0)
		return (NULL);
	new_array = (int*)malloc(sizeof(int) * (var.count));
	var.j = 0;
	while (var.j < len)
	{
		add_room_in_array(lemin, array, &var, &new_array);
		var.j++;
	}
	return (new_array);
}
