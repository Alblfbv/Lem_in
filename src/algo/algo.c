/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:34:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/10 18:00:51 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_path_len(t_room *room, t_lem lem)
{
	t_room		*tmp_r;
	t_neighbor	*tmp_n;
	int			len;

	tmp_r = room;
	len = 0;
	while (tmp_r != lem.end_room)
	{
		tmp_n = tmp_r->neighbor;
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		len++;
		tmp_r = tmp_n->room;
	}
	return (len);
}

t_room	**ft_fill_path(t_room **all_path, t_room *first, int len, t_lem lem)
{
	int			i;
	t_room		*tmp_r;
	t_neighbor	*tmp_n;

	ft_printf("Taille du chemin : %d\n", len);
	all_path = (t_room**)malloc(sizeof(t_room*) * (len + 1 + 1));
	all_path[len + 1] = 0;
	all_path[0] = lem.start_room;
	tmp_r = first;
	i = 1;
	while (tmp_r != lem.end_room)
	{
		tmp_n = tmp_r->neighbor;
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		all_path[i] = tmp_n->room;
		tmp_r = tmp_n->room;
		i++;
	}
	return (all_path);
}

t_room	****ft_store_path(t_room ****all_path, t_lem lem)
{
	t_room		*tmp_r;
	t_neighbor	*tmp_n;
	int			nb_path;
	int			len;
	int			i;
	int			j;

	tmp_r = lem.start_room;
	tmp_n = tmp_r->neighbor;
	nb_path = 0;
	i = 0;
	j = 0;
	while (tmp_n->next != NULL)
	{
		if (tmp_n->flow == 1)
			nb_path++;
		tmp_n = tmp_n->next;
	}
	ft_printf("Nombre de chemins : %d\n", nb_path);
	while (all_path[j] != 0)
		j++;
	all_path[j] = (t_room***)malloc(sizeof(t_room**) * (nb_path + 1));
	all_path[j][nb_path] = 0;
	tmp_n = tmp_r->neighbor;
	while (i < nb_path)
	{
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		len = ft_path_len(tmp_n->room, lem);
		all_path[j][i] = ft_fill_path(all_path[j][i], tmp_n->room, len, lem);
		i++;
	}
	return (all_path);
}

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
			n_forth->flow = 1;
		}
		if (i != 0)
		{
			n_back = shortest_path[i]->neighbor;
			while (n_back->room != shortest_path[i - 1])
				n_back = n_back->next;
			n_back->flow = -1;
		}
		i++;
	}
}

void	ft_print_paths(t_room ****all_path, t_lem lem)
{
	int	i;
	int	j;

	i = 1;
	(void)all_path;
	while (*all_path != 0)
	{
		ft_printf("Edmonds-Karp n*%d :\n", i);
		j = 1;
		while (**all_path != 0)
		{
			ft_printf("Path n*%d :", j);
			while (***all_path != 0)
			{
				ft_printf(" %s -", (***all_path)->name);
				**all_path = **all_path + 1;
			}
			*all_path = *all_path + 1;
			j++;
		}
		i++;
		all_path = all_path + 1;
		ft_printf("\n\n");
	}
}

int		ft_count_bottleneck(t_lem lem)
{
	t_neighbor	*tmp_n;
	int			b_neck_start;
	int			b_neck_end;

	b_neck_start = 0;
	tmp_n = ((lem.start_room)->neighbor);
	while (tmp_n->next != NULL)
	{
		if (b_neck_start == 0)
			b_neck_start++;
		tmp_n = tmp_n->next;
		b_neck_start++;
	}
	b_neck_end = 0;
	tmp_n = ((lem.end_room)->neighbor);
	while (tmp_n->next != NULL)
	{
		if (b_neck_end == 0)
			b_neck_end++;
		tmp_n = tmp_n->next;
		b_neck_end++;
	}
	return ((b_neck_end > b_neck_start) ? b_neck_end : b_neck_start);
}

void	ft_print_bfs(t_room **shortest_path)
{
	int	i;

	i = 0;
	ft_printf("shortest path = ");
	while (shortest_path && shortest_path[i] != 0)
	{
		ft_printf(" %s -", shortest_path[i]->name);
		i++;
	}
	ft_printf("\n");
}

int		ft_algo(t_room **room, t_lem lem)
{
	int		i;
	t_room	**shortest_path;
	t_room	****all_path;

	i = 0;
	lem.nb_path = ft_count_bottleneck(lem);
	all_path = (t_room****)malloc(sizeof(t_room***) * (lem.nb_path + 1));
	while (i < lem.nb_path)
	{
		all_path[i] = 0;
		i++;
	}	
	all_path[lem.nb_path] = 0;
	i = 0;
	while (i < lem.nb_path)
	{
		shortest_path = ft_bfs(room, lem);
		ft_printf("\n\n\n\n");
		ft_print_bfs(shortest_path);
		ft_edmond_karp(shortest_path);
		all_path = ft_store_path(all_path, lem);
		free(shortest_path);
		i++;
	}
	ft_print_paths(all_path, lem);
	return (1);
}
