/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:37:47 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/19 17:21:30 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	**ft_fill_path(t_room **all_path, t_room *first, int len, t_lem lem)
{
	int			i;
	t_room		*tmp_r;
	t_neighbor	*tmp_n;

	all_path = (t_room**)malloc(sizeof(t_room*) * (len + 1));
	all_path[len] = 0;
	all_path[0] = lem.start_room;
	tmp_r = first;
	i = 1;
	while (tmp_r != lem.end_room)
	{
		all_path[i] = tmp_r;
		tmp_n = tmp_r->neighbor;
		while (tmp_n->flow != 1 || tmp_n->storage_flow == 1)
			tmp_n = tmp_n->next;
		tmp_n->storage_flow = 1;
		tmp_r = tmp_n->room;
		i++;
	}
	all_path[i] = tmp_r;
	ft_printf("\n\n");
	return (all_path);
}

t_room			****ft_store_path(t_room ****all_path, t_lem lem)
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
	j = 0;
	while (tmp_n != NULL)
	{
		if (tmp_n->flow == 1)
		{
			nb_path++;
		}
		tmp_n = tmp_n->next;
	}
	while (all_path[j] != 0)
		j++;
	all_path[j] = (t_room***)malloc(sizeof(t_room**) * (nb_path + 1));
	all_path[j][nb_path] = 0;
	tmp_n = tmp_r->neighbor;
	i = 0;
	while (i < nb_path)
	{
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		len = ft_path_len(tmp_n->room, lem);
		all_path[j][i] = ft_fill_path(all_path[j][i], tmp_n->room, len, lem);
		tmp_n = tmp_n->next;
		i++;
	}
	return (all_path);
}

int		**ft_create_path_tab(t_room ****all_path)
{
	int	i;
	int	j;
	int	k;
	int	**tab;

	i = 0;
	while (all_path[i] != 0)
		i++;
	tab = (int**)malloc(sizeof(int*) * (i + 1));
	tab[i] = 0;
	i = 0;
	while (all_path[i] != 0)
	{
		j = 0;
		while (all_path[i][j] != 0)
			j++;
		tab[i] = (int*)malloc(sizeof(int) * (j + 1));
		tab[i][j] = 0;
		i++;
	}
	i = 0;
	while (all_path[i] != 0)
	{
		j = 0;
		while (all_path[i][j] != 0)
		{
			k = 0;
			while (all_path[i][j][k] != 0)
				k++;
			tab[i][j] = k - 1;
			j++;
		}
		i++;
	}
	return (tab);
}

void	ft_print_paths(t_room ****all_path, t_lem lem)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (all_path[i] != 0)
	{
		ft_printf("\nEdmonds-Karp n*%d :", i + 1);
		j = 0;
		while (all_path[i][j] != 0)
		{
			ft_printf("test");
			k = 0;
			ft_printf("\nPath n*%d :", j + 1);
			while (all_path[i][j][k] != 0)
			{
				ft_printf(" %s -", all_path[i][j][k]->name);
				k++;
			}
			j++;
		}
		i++;
		ft_printf("\n\n");
	}
}

