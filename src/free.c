/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 19:44:19 by bdebbie           #+#    #+#             */
/*   Updated: 2020/03/04 19:44:20 by bdebbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	coords_free_and_error(t_lem *ret, char **split, char *line)
{
	free(ret->rooms);
	free_split(split);
	error_case(line);
}

void	free_split(char **split)
{
	int i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_all(t_lem lemin)
{
	int i;

	i = 0;
	while (i < lemin.r_count)
		free(lemin.links[i++]);
	free(lemin.links);
	free(lemin.rooms);
}

void	free_paths(t_path *paths)
{
	t_cont *to_free_cont;
	t_path *to_free_path;

	while (paths != NULL)
	{
		while (paths->path != NULL)
		{
			to_free_cont = paths->path;
			paths->path = paths->path->next;
			free(to_free_cont);
		}
		to_free_path = paths;
		paths = paths->next;
		free(to_free_path);
	}
}
