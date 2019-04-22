/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:34:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/22 13:24:01 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


void	ft_edmond_karp(t_room **shortest_path)
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

int		ft_count_bottleneck(t_lem lem)
{
	t_neighbor	*tmp_n;
	int			b_neck_start;
	int			b_neck_end;

	b_neck_start = 0;
	tmp_n = ((lem.start_room)->neighbor);
	while (tmp_n != NULL)
	{
		b_neck_start++;
		tmp_n = tmp_n->next;
	}
	b_neck_end = 0;
	tmp_n = ((lem.end_room)->neighbor);
	while (tmp_n != NULL)
	{
		b_neck_end++;
		tmp_n = tmp_n->next;
	}
	return ((b_neck_end >= b_neck_start) ? b_neck_start : b_neck_end);
}

void	ft_init_storage_flow(t_room **room, t_lem lem)
{
	t_neighbor	*tmp_n;
	int			i;

	i = 0;
	while (i < lem.nb_room)
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

int		ft_algo(t_room **room, t_lem lem)
{
	int		i;
	t_room	**shortest_path;
	t_path	***all_path;

	i = 0;
	lem.nb_path = ft_count_bottleneck(lem);
	all_path = (t_path***)malloc(sizeof(t_path**) * (lem.nb_path + 1));
	while (i <= lem.nb_path)
	{
		all_path[i] = 0;
		i++;
	}	
	i = 0;
	while (i < lem.nb_path)
	{
		if ((shortest_path = ft_bfs(room, lem)) != NULL)
		{
		//	ft_print_bfs(shortest_path);
			ft_edmond_karp(shortest_path);
			ft_init_storage_flow(room, lem);
			all_path = ft_store_path(all_path, lem);
			free(shortest_path);
			i++;
		}
		else
			break ;
	}
	ft_print_paths(all_path, lem);
	ft_chose_best_path(all_path, lem);
	return (1);
}
