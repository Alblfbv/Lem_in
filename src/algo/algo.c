/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:34:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/26 15:56:58 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_edmond_karp(t_room **shortest_path)
{
	t_neighbor	*n_forth;
	t_neighbor	*n_back;
	int			i;

	i = 0;
	while (shortest_path && shortest_path[i] != 0)
	{
		if (shortest_path[i + 1] != 0)
		{
			n_forth = shortest_path[i]->neighbor;
			while (n_forth->room != shortest_path[i + 1])
				n_forth = n_forth->next;
			n_forth->flow = n_forth->flow + 1;
		}
		if (i != 0)
		{
			shortest_path[i]->flow = 1;
			n_back = shortest_path[i]->neighbor;
			while (n_back->room != shortest_path[i - 1])
				n_back = n_back->next;
			n_back->flow = n_back->flow - 1;
		}
		i++;
	}
}

static int	ft_count_bottleneck(t_data data)
{
	t_neighbor	*tmp_n;
	int			b_neck_start;
	int			b_neck_end;

	if (data.start_room == NULL || data.end_room == NULL)
		return (0);
	b_neck_start = 0;
	tmp_n = ((data.start_room)->neighbor);
	while (tmp_n != NULL)
	{
		b_neck_start++;
		tmp_n = tmp_n->next;
	}
	b_neck_end = 0;
	tmp_n = ((data.end_room)->neighbor);
	while (tmp_n != NULL)
	{
		b_neck_end++;
		tmp_n = tmp_n->next;
	}
	return ((b_neck_end >= b_neck_start) ? b_neck_start : b_neck_end);
}

static void	ft_init_storage_flow(t_room **room, t_data data)
{
	t_neighbor	*tmp_n;
	int			i;

	i = 0;
	while (i < data.nb_room)
	{
		tmp_n = room[i]->neighbor;
		while (tmp_n != NULL)
		{
			tmp_n->storage_flow = 0;
			tmp_n = tmp_n->next;
		}
		i++;
	}
}

static void	ft_bfs_loop(t_data data, t_room **room, t_path ****all_path)
{
	t_room	**shortest_path;
	int		i;

	i = 0;
	while (i < data.nb_path)
	{
		if ((shortest_path = ft_bfs(room, data)) != NULL)
		{
			//ft_print_bfs(shortest_path);
			ft_edmond_karp(shortest_path);
			ft_init_storage_flow(room, data);
			*all_path = ft_store_path(*all_path, data);
			free(shortest_path);
			i++;
		}
		else
			break ;
	}
}

int			ft_algo(t_room **room, t_data data)
{
	int		i;
	t_path	***all_path;
	t_path	**best_path;

	if (!(data.nb_path = ft_count_bottleneck(data)))
		return (0);
	all_path = (t_path***)malloc(sizeof(t_path**) * (data.nb_path + 1));
	i = -1;
	while (++i <= data.nb_path)
		all_path[i] = 0;
	ft_bfs_loop(data, room, &all_path);
	//ft_print_paths(all_path);
	best_path = ft_chose_best_path(all_path, data);
	if (best_path != NULL)
	{
		ft_lstprint_str(*data.instructions);
		ft_printf("\n");
		ft_lem_manage(best_path, data);
		ft_free_paths(all_path);
		return (1);
	}
	ft_free_paths(all_path);
	return (0);
}
