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
	// int ret;
	int i;
	long long num;

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
			if (line[i] < '0' || line[i] > '9')
				error_case(line);
		num = ft_atoi(line);
		if (num <= 0 || num > 0x7fffffff)
		{
			free(ret->rooms);
			error_case(line);
		}
		ret->a_count = num;
		free(line);
		// printf("%d - asdasdasd\n", ret->a_count);
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
	ret->memory = 50;
	ret->rooms = (t_room*)malloc(sizeof(t_room) * 50);
}

int		check_comment(char *line, t_lem *ret, int *is_soe)
{
	if (ft_strcmp("##start", line) == 0)
	{
		free(line);
		if (ret->start != -1)
		{
			printf("hey7\n");
			error_case(ret->rooms);
		}
		*is_soe = 1;
		return (1);
	}
	else if (ft_strcmp("##end", line) == 0)
	{
		free(line);
		if (ret->end != -1)
		{
			printf("hey8\n");
			error_case(ret->rooms);
		}
		*is_soe = 2;
		return (1);
	}
	else if (line[0] == '#')
	{
		if (line[1] == '#')
		{
			printf("hey9\n");
			free(ret->rooms);
			error_case(line);
		}
		free(line);
		return (1);
	}
	return (0);
}

void	increase_array(t_lem *ret)
{
	t_room *copy_array;
	int i;

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
	// for (int i = 0; i < ret->r_count; i++) {
	// 	printf("%s\n", ret->rooms[i].name);
	// }
	// printf("__________________________\n");
}

t_room	get_room(char *line, t_lem *ret, int is_soe)
{
	char **split;
	int len;
	t_room room_ret;
	int i;
	
	len = 0;
	// if (ret->r_count >= ret->memory)
	// {
	// 	increase_array(ret);
	// 	printf("mem - %d\n", ret->memory);
	// }
	split = ft_strsplit(line, ' ');
	while (split[len] != NULL)
		len++;
	if (len != 3)
	{
		printf("r_count - %d line - |%s| hey1\n", ret->r_count,  line);
		free(line);
		error_case(ret->rooms);
	}
	i = -1;
	while (split[1][++i])
			if (split[1][i] < '0' || split[1][i] > '9')
			{
				printf("hey2\n");
				free(ret->rooms);
				error_case(line);
			}
	i = -1;
	while (split[2][++i])
			if (split[2][i] < '0' || split[2][i] > '9')
			{
				printf("hey3\n");
				free(ret->rooms);
				error_case(line);
			}
	room_ret.x = ft_atoi(split[1]);
	room_ret.y = ft_atoi(split[2]);
	ret->r_count++;
	ft_strcpy(room_ret.name, split[0]);
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	// room_ret.is_start == is_soe
	return (room_ret);
}

void	add_links(char *line, t_lem *ret)
{
	char **split;
	int len;
	int count;
	int link1;
	int link2;

	link1 = 0;
	link2 = 0;
	count = 0;
	len = -1;
	split = ft_strsplit(line, '-');
	while (split[++len])
		;
	if (len != 2)
	{
		printf("dsad0\n");
		len = -1;
		printf("split0\n");
		while (split[++len])
			free(split[len]);
		free(split);
		printf("split1\n");
		printf("dsad\n");
		free(ret->rooms);
		len = 0;
		printf("ds111\n");
		// while (len != ret->r_count + 1)
		// {
		// 	free(ret->links[len]);
		// 	len++;
		// }
		printf("dsad\n");
		// free(ret);
		error_case(line);
	}
	len = -1;
	while (++len != ret->r_count)
	{

		if (ft_strcmp(ret->rooms[len].name, split[0]) == 0 || ft_strcmp(ret->rooms[len].name, split[1]) == 0)
		{
			link1 = ft_strcmp(ret->rooms[len].name, split[0]) == 0 ? len : link1;
			link2 = ft_strcmp(ret->rooms[len].name, split[1]) == 0 ? len : link2;
			count++;
		}
	}
	if (count != 2)
	{
		printf("dsad2\n");
		len = -1;
		while (split[++len])
		{
			printf("split - |%s| %d\n", split[len], len);
			free(split[len]);
		}
		free(split);
		free(ret->rooms);
		// free(ret);
		printf("hey91\n");
		error_case(line);
	}
	else
	{
		ret->links[link1][link2] = 1;
		ret->links[link2][link1] = 1;
		len = -1;
		while (split[++len])
		{
			printf("split - |%s| %d\n", split[len], len);
			free(split[len]);
		}
		free(split);
	}
	
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

t_lem	validate()
{
	char *line;
	t_lem ret;
	int is_soe;
	int i;
	int ans;

	lem_init(&ret, &is_soe, &i);
	ant_count(line, &ret);
	while ((ans = get_next_line(0, &line)))
	{
		// printf("%s\n", line);
		if (check_comment(line, &ret, &is_soe))
			continue ;
		if (ft_strchr(line, '-') != NULL)
			break;
		ret.start = is_soe == 1 ? i : ret.start;
		ret.end = is_soe == 2 ? i : ret.end;
		if (ret.r_count >= ret.memory)
	{
		increase_array(&ret);
	}
		ret.rooms[i++] = get_room(line, &ret, is_soe);
		is_soe = -1;
		free(line);
		// if (ft_strchr(line, '-') != NULL)
		// 	add_links(line, &ret);
		// if (ft_strchr(line, '-') != NULL)
		// 	break;
	}
	if (ret.start == -1 || ret.end == -1 || ans == 0)
	{
		printf("hey4\n");
		error_case(ret.rooms);
	}
	//printf("hey5\n");
	printf("r_count - %d\n", ret.r_count);
	create_array_links(&ret);
	printf("hey5\n");
	int a;
	while (1)
	{
		if (check_comment(line, &ret, &is_soe))
		{
			a = get_next_line(0, &line);
			if (a <= 0)
				break;
			continue ;
		}
		add_links(line, &ret);
		free (line);
		a = get_next_line(0, &line);
		// printf("aaa - %d\n", a);
		if (a <= 0)
			break;
	}
	return (ret);
}

void	free_all(t_lem lemin)
{
	for (int i = 0; i < lemin.r_count; i++) {
		free(lemin.links[i]);
	}
	free(lemin.links);
	free(lemin.rooms);
}

int main(void)
{
	t_lem lemin = validate();


	// printf("_______________________________________________________________________________________________________________________\n");
	// printf("%d - rooms count, %d - ant count, %d - start, %d - end\n", lemin.r_count, lemin.a_count, lemin.start, lemin.end);
	// for (int i = 0; i < lemin.r_count; i++) {
	// 	for (int j = 0; j < lemin.r_count; j++) {
	// 		printf("%-3d", lemin.links[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// for (int i = 0; i < lemin.r_count; i++) {
	// 	printf("%s\n", lemin.rooms[i].name);
	// }
	free_all(lemin);
	return (0);
}
