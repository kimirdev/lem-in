/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
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
	write(1, "Error\n", 6);
	exit(0);
}

void	ant_count(char *line, t_lem *ret)
{
	int ret;
	int i;

	while (get_next_line(0, &line))
	{
		if (line[0] == '#')
		{
			if (line[1] == '#')
				error_case(line);
			free(line);
			continue ;
		}
		i = -1;
		while (line[++i])
			if (line[0] == '+' && (line[i] < '0' || line[i] > '9'))
				error_case(line);
		ret->a_count = ft_atoi(line);
		return ;
	}
}

void	lem_init(t_lem *ret, int *a, int *i)
{
	ret->start = -1;
	ret->end = -1;
	ret->r_count = 0;
	ret->a_count = 0;
	*a = 0;
	*i = 0;
	ret->rooms = (t_rooms*)malloc(sizeof(t_rooms) * 50);
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
	else if (line[0] == '#')
	{
		if (line[1] == '#')
		{
			free(ret->rooms);
			error_case(line);
		}
		free(line);
		return (1);
	}
	return (0)
}

t_room	get_room(char *line, t_lem *ret, int is_soe)
{
	char **split;
	int len;
	t_room room_ret;
	int i;

	split = ft_strsplit(line, " ");
	while (split[len] != NULL)
		len++;
	if (len != 3)
	{
		free(line);
		error_case(ret->rooms);
	}
	i = -1;
	while (split[1][++i])
			if (split[1][i] == '+' && (split[1][i] < '0' || split[1][i] > '9'))
			{
				free(ret->rooms);
				error_case(line);
			}
	i = -1;
	while (split[2][++i])
			if (split[2][i] == '+' && (split[2][i] < '0' || split[2][i] > '9'))
			{
				free(ret->rooms);
				error_case(line);
			}
	room_ret.x = ft_atoi(split[1]);
	room_ret.y = ft_atoi(split[2]);
	ft_strcpy(room_ret.name, split[0]);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (room_ret);
}

t_lem	validate()
{
	char *line;
	t_lem ret;
	int is_soe;
	int i;

	ant_count(line, &ret);
	lem_init(&ret, &is_soe, &i);
	while (get_next_line(0, &line))
	{
		if (check_comment(line, &ret, &is_soe))
			continue ;
		ret->rooms[i++] = get_room(line, &ret, is_soe);
	}
}

int main(void)
{
	t_lem lemin = validate();
	return (0);
}
