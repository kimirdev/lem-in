/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_links(int *link1, int *link2, t_lem *ret, char **split)
{
	int len;
	int count;

	len = -1;
	*link1 = 0;
	*link2 = 0;
	count = 0;
	while (++len != ret->r_count)
	{
		if (ft_strcmp(ret->rooms[len].name, split[0]) == 0 ||
			ft_strcmp(ret->rooms[len].name, split[1]) == 0)
		{
			*link1 = ft_strcmp(ret->rooms[len].name, split[0]) == 0 \
														? len : *link1;
			*link2 = ft_strcmp(ret->rooms[len].name, split[1]) == 0 \
														? len : *link2;
			count++;
		}
	}
	return (count);
}

int		is_link(int link1, int link2, t_lem *ret, int count)
{
	if (count != 2)
	{
		free(ret->rooms);
		return (0);
	}
	else
	{
		ret->links[link1][link2] = 1;
		ret->links[link2][link1] = 1;
		return (1);
	}
}

void	add_links(char *line, t_lem *ret)
{
	char	**split;
	int		len;
	int		count;
	int		link1;
	int		link2;

	len = -1;
	split = ft_strsplit(line, '-');
	while (split[++len])
		;
	if (len != 2)
	{
		free_split(split);
		free(ret->rooms);
		error_case(line);
	}
	len = -1;
	count = check_links(&link1, &link2, ret, split);
	free_split(split);
	if (!is_link(link1, link2, ret, count))
		error_case(line);
}

void	create_array_links(t_lem *ret)
{
	int i;
	int j;

	i = 0;
	ret->links = (int **)malloc(sizeof(int *) * (ret->r_count));
	while (i != ret->r_count)
	{
		j = 0;
		ret->links[i] = (int *)malloc(sizeof(int) * (ret->r_count));
		while (j != ret->r_count)
		{
			ret->links[i][j] = 0;
			j++;
		}
		i++;
	}
}

t_lem	array_links(t_lem ret, int is_soe, int ans, char *line)
{
	if (ret.start == -1 || ret.end == -1 || ans == 0)
		error_case(ret.rooms);
	create_array_links(&ret);
	while (1)
	{
		if (check_comment(line, &ret, &is_soe))
		{
			if (get_next_line(0, &line) <= 0)
				break ;
			print_line(line);
			continue ;
		}
		add_links(line, &ret);
		free(line);
		if (get_next_line(0, &line) <= 0)
			break ;
		print_line(line);
	}
	write(1, "\n", 1);
	return (ret);
}
