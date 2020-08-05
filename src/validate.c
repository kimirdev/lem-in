/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	increase_array(t_lem *ret)
{
	t_room	*copy_array;
	int		i;

	copy_array = (t_room*)malloc(sizeof(t_room) * ret->memory * 2);
	ret->memory *= 2;
	i = 0;
	while (i < ret->r_count)
	{
		copy_array[i] = ret->rooms[i];
		i++;
	}
	free(ret->rooms);
	ret->rooms = copy_array;
}

t_room	get_coords(char **split, char *line, t_lem *ret, t_room room_ret)
{
	int i;

	i = -1;
	while (split[1][++i])
		if (split[1][i] < '0' || split[1][i] > '9')
			coords_free_and_error(ret, split, line);
	i = -1;
	while (split[2][++i])
		if (split[2][i] < '0' || split[2][i] > '9')
			coords_free_and_error(ret, split, line);
	room_ret.x = ft_atoi(split[1]);
	room_ret.y = ft_atoi(split[2]);
	i = -1;
	while (++i < ret->r_count)
		if (ret->rooms[i].x == room_ret.x && ret->rooms[i].y == room_ret.y)
			coords_free_and_error(ret, split, line);
	return (room_ret);
}

t_room	get_room(char *line, t_lem *ret)
{
	char	**split;
	int		len;
	t_room	room_ret;

	len = 0;
	room_ret.level = -1;
	split = ft_strsplit(line, ' ');
	while (split[len] != NULL)
		len++;
	if (len != 3)
		coords_free_and_error(ret, split, line);
	room_ret = get_coords(split, line, ret, room_ret);
	ret->r_count++;
	if (split[0][0] == 'L')
		coords_free_and_error(ret, split, line);
	ft_strcpy(room_ret.name, split[0]);
	free_split(split);
	return (room_ret);
}

t_lem	validate(void)
{
	char	*line;
	t_lem	ret;
	int		is_soe;
	int		i;
	int		ans;

	line = NULL;
	lem_init(&ret, &is_soe, &i);
	ant_count(line, &ret);
	while ((ans = get_next_line(0, &line)))
	{
		print_line(line);
		if (check_comment(line, &ret, &is_soe))
			continue ;
		if (ft_strchr(line, '-') != NULL)
			break ;
		ret.start = is_soe == 1 ? i : ret.start;
		ret.end = is_soe == 2 ? i : ret.end;
		if (ret.r_count >= ret.memory)
			increase_array(&ret);
		ret.rooms[i++] = get_room(line, &ret);
		is_soe = -1;
		free(line);
	}
	return (array_links(ret, is_soe, ans, line));
}
