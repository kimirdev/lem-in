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
	room_ret.level = -1;
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

int	count_exit(t_lem *lemin)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (i != lemin->r_count)
	{
		if (lemin->links[lemin->end][i] == 1)
			count++;
		i++;
	}
	return (count);
}

int *create_first_array(t_lem *lemin, int *count_end, int *len)
{
	int i;
	int start;
	int count_entrance;
	int* array_1;
	int j;

	j = 0;
	count_entrance = 0;
	start = lemin->start;
	// printf("lemin_start - %d\n", start);
	i = 0;
	while (i < lemin->r_count)
	{
		if (lemin->links[start][i] == 1 && i != start)
		{
			if (i == lemin->end)
			{
				(*count_end)--;
			}
			else
				count_entrance++;
		}
		i++;
	}
	//printf("count_entrance - %d\n", count_entrance);
	array_1 = (int*)malloc(sizeof(int) * (count_entrance)); // + 1
	*len = count_entrance;
	i = 0;
	while (i < lemin->r_count)
	{
		if (lemin->links[start][i] == 1 && i != start)
		{
			if (i != lemin->end)
			{
				//printf("j - %d, i - %d\n", j, i);
				array_1[j] = i;
				lemin->rooms[i].level = lemin->rooms[start].level + 1;
				j++;
			}
		}
		i++;
	}
	//printf("________________\n");
	return (array_1);
}

void free_array(int **array)
{
	free(*array);
}

int *create_array(int *array, int *count_end, t_lem *lemin, int len, int *len_new)
{
	int *new_array;
	int i;
	int j;
	int count;
	int k;
	int z;
	int check = 0;
	k = 0;
// printf("hey1___, array[j] - %d\n", array[0]);
	count = 0;
	j = 0;
	//printf("___________________\n");
	//printf("len - %d\n", len);
	while (j < len)
	{
		i = 0;
		// printf("len in while = %d\n", len);
		while (i < lemin->r_count)
		{
			//printf("%d - i\n", array[j]);
			if (lemin->links[array[j]][i] == 1)
			{
				// printf("hey\n");
				if (lemin->rooms[i].level > lemin->rooms[array[j]].level + 1 && i != lemin->end)
				{
					lemin->rooms[i].level = lemin->rooms[array[j]].level + 1;
				}
				else if (i != lemin->end && lemin->rooms[i].level == -1)
				{
					lemin->rooms[i].level = lemin->rooms[array[j]].level + 1;
					count++;
				}
			}
			// else if (lemin->links[array[j]][i] == 1 && i == lemin->end)
			// {
			// 	printf("hey_____\n");
			// 	(*count_end)--;
			// }
			i++;
		}
		// printf("aew\n");
		j++;
	}
	// printf("hey1_2\n");
	*len_new = count;
	//printf("len_new - %d, count - %d\n", *len_new, count);
	new_array = (int*)malloc(sizeof(int) * (count));
	j = 0;
	while (j < len)
	{
		i = 0;
		while (i < lemin->r_count)
		{
			if (lemin->links[array[j]][i] == 1 && i == lemin->end)
			{
				(*count_end)--;
				
			}
			else if (lemin->links[array[j]][i] == 1 && lemin->rooms[i].level > lemin->rooms[array[j]].level)
			{
				//lemin->rooms[i].level = lemin->rooms[array[j]].level + 1;
				// printf("j - %d, i - %d\n", array[j], i);
				z = 0;
				check = 0;
				while (z != k)
				{
					if (i == new_array[z])
						check = 1;
					z++;
				}
				if (check == 0)
				{
					//printf("j - %d, i - %d\n", array[j], i);
					new_array[k] = i;
					k++;
				}
			}
			i++;
		}
		j++;
	}
	// printf("k = %d\n", k);
// printf("hey2___, new_array[0] - %d\n", new_array[0]);
//printf("___________________\n");
	return (new_array);
}

void	add_level(t_lem *lemin)
{
	lemin->rooms[lemin->start].level = 0;
	lemin->rooms[lemin->end].level = 2147483647;
	int *array_1;
	int *array_2;
	int count_end;
	int len_1;
	int len_2;

	// count_end = count_exit(lemin);
	//count_entrance = 0;
	//printf("%d - count_end\n", count_end);
	len_1 = 0;
	len_2 = 0;
	array_1 = create_first_array(lemin, &count_end, &len_1);
	while (count_end != 0)
	{
		array_2 = create_array(array_1, &count_end, lemin, len_1, &len_2);
		//printf("first, end - %d, start - %d\n", lemin->end, lemin->start);
		free_array(&array_1);
		if (len_2 == 0)
		{
			//printf("break_1\n");
			break;
		}
		//printf("first_n\n");
		array_1 = create_array(array_2, &count_end, lemin, len_2, &len_1);
		//printf("second\n");
		free_array(&array_2);
		if (len_1 == 0)
			break;
		//printf("len_1 - %d\n", len_1);
		// array_2 = create_array(array_1, &count_end, lemin, len_1, &len_2);
		// free_array(&array_1);
		// printf("count_end - %d, array_2 - %d \n", count_end, array_2[0]);
		// array_1 = create_array(array_2, &count_end, lemin, len_2, &len_1);
		// free_array(&array_2);
		// printf("count_end - %d, array_2 - %d \n", count_end, array_2[0]);
	}
}

void	dfs_in_out(t_lem *lemin)
{
	int i = 0;
	int j;

	while (i < lemin->r_count)
	{
		j = i;
		while (j < lemin->r_count)
		{
			if (lemin->rooms[i].level == lemin->rooms[j].level && lemin->links[i][j] == 1)
			{
				lemin->links[i][j] = 0;
				lemin->links[j][i] = 0; // я добавил
			}
			if (lemin->links[i][j] == 1)
			{
				if (lemin->rooms[i].level < lemin->rooms[j].level)
				{
					lemin->rooms[i].out++;
					lemin->rooms[j].in++;
				}
				else
				{
					lemin->rooms[j].out++;
					lemin->rooms[i].in++;	
				}
			}
			j++;
		}
		i++;
	}
}

void	count_in_out(t_lem *lemin)
{
	int i = 0;

	while (i < lemin->r_count)
	{
		lemin->rooms[i].in = 0;
		lemin->rooms[i].out = 0;
		i++;
	}
	dfs_in_out(lemin);

	// CHECK INPUTS OUTPUTS

	for (int q = 0; q < lemin->r_count; q++)
	{
		printf("%s: in=%d | out=%d\n", lemin->rooms[q].name, lemin->rooms[q].in, lemin->rooms[q].out);
	}
}

void	delete_in(t_lem *lemin, int pos)
{
	int max;
	int room;
	int i;

	i = 0;
	max = 10000000;
	while (i != lemin->r_count)
	{
		if (lemin->links[pos][i] == 1 && lemin->rooms[pos].level > lemin->rooms[i].level && max > lemin->rooms[i].out && i != lemin->end)
		{
			max = lemin->rooms[i].out;
			room = i;
		}
		i++; 
	}
	i = 0;
	while (i != lemin->r_count)
	{
		if (lemin->links[pos][i] == 1 && i != room && lemin->rooms[pos].level > lemin->rooms[i].level && i != lemin->end)
		{
			//printf("zashel\n");
			lemin->links[pos][i] = 0;
			lemin->links[i][pos] = 0;
			lemin->rooms[i].out--;
			lemin->rooms[pos].in--;
		}
		i++;
	}

}

void	check_in(t_lem *lemin)
{
	int i;

	i = 0;
	while (i != lemin->r_count)
	{
		if (lemin->rooms[i].in > 1)
		{
			//printf("ya tut\n");
			delete_in(lemin, i);
		}
		i++;
	}
}

int main(void)
{
	t_lem lemin = validate();
	add_level(&lemin);
	count_in_out(&lemin);
	check_in(&lemin);

	// int i = 0;
	// int c = 0;
	// while (i < lemin.r_count)
	// {
	// 	if (lemin.links[90][i] == 1 && i != lemin.end)
	// 	{
	// 		c++;
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (i < lemin.r_count)
	// {
	// 	if (lemin.links[106][i] == 1 && i != lemin.end)
	// 	{
	// 		c++;
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (i < lemin.r_count)
	// {
	// 	if (lemin.links[150][i] == 1 && i != lemin.end)
	// 	{
	// 		c++;
	// 	}
	// 	i++;
	// }
	// printf("c - %d\n", c);

	printf("_______________________________________________________________________________________________________________________\n");
	printf("%d - rooms count, %d - ant count, %d - start, %d - end\n", lemin.r_count, lemin.a_count, lemin.start, lemin.end);
	for (int i = 0; i < lemin.r_count; i++) {
		for (int j = 0; j < lemin.r_count; j++) {
			printf("%-3d", lemin.links[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < lemin.r_count; i++) {
		printf("%s, %d-level, %d-in, %d-out\n", lemin.rooms[i].name, lemin.rooms[i].level, lemin.rooms[i].in, lemin.rooms[i].out);
	}
	free_all(lemin);
	return (0);
}
