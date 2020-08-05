/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ants_max_min_bounds(long long num, t_lem *ret, char *line)
{
	if (num <= 0 || num > 0x7fffffff)
	{
		free(ret->rooms);
		error_case(line);
	}
}

void	ant_count(char *line, t_lem *ret)
{
	int			i;
	long long	num;

	while (get_next_line(0, &line))
	{
		print_line(line);
		if (line[0] == '#')
		{
			if (line[1] == '#')
				error_case(line);
			free(line);
			continue ;
		}
		i = -1;
		while (line[++i])
			if (line[i] < '0' || line[i] > '9')
				error_case(line);
		num = ft_atoi(line);
		ants_max_min_bounds(num, ret, line);
		ret->a_count = num;
		free(line);
		return ;
	}
}

int		sys_or_simple_comm(char *line, t_lem *ret)
{
	if (line[0] == '#')
	{
		if (line[1] == '#')
		{
			free(ret->rooms);
			error_case(line);
		}
		free(line);
		return (1);
	}
	return (0);
}

int		check_comment(char *line, t_lem *ret, int *is_soe)
{
	if (ft_strcmp("##start", line) == 0)
	{
		free(line);
		if (ret->start != -1)
			error_case(ret->rooms);
		*is_soe = 1;
		return (1);
	}
	else if (ft_strcmp("##end", line) == 0)
	{
		free(line);
		if (ret->end != -1)
			error_case(ret->rooms);
		*is_soe = 2;
		return (1);
	}
	return (sys_or_simple_comm(line, ret));
}
