/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:37:47 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/23 21:13:22 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_path_len(t_room *room, t_data data)
{
	t_room		*tmp_r;
	t_neighbor	*tmp_n;
	int			len;

	tmp_r = room;
	len = 1;
	while (tmp_r != data.end_room)
	{
		tmp_n = tmp_r->neighbor;
		while (tmp_n->flow != 1 || tmp_n->storage_flow == 1)
			tmp_n = tmp_n->next;
		len++;
		tmp_r = tmp_n->room;
	}
	len++;
	return (len);
}

static t_path	*ft_fill_path(t_path *path, t_room *first, int len, t_data data)
{
	int			i;
	t_room		*tmp_r;
	t_neighbor	*tmp_n;

	path = (t_path*)malloc(sizeof(t_path));
	path->path = (t_room**)malloc(sizeof(t_room*) * (len + 1));
	path->path[len] = 0;
	path->path[0] = data.start_room;
	tmp_r = first;
	i = 1;
	while (tmp_r != data.end_room)
	{
		path->path[i] = tmp_r;
		tmp_n = tmp_r->neighbor;
		while (tmp_n->flow != 1 || tmp_n->storage_flow == 1)
			tmp_n = tmp_n->next;
		tmp_n->storage_flow = 1;
		tmp_r = tmp_n->room;
		i++;
	}
	path->path[i] = tmp_r;
	path->length = i;
	path->lems = 0;
	return (path);
}

t_path	***ft_store_path(t_path ***all_path, t_data data)
{
	t_room		*tmp_r;
	t_neighbor	*tmp_n;
	int			nb_path;
	int			len;
	int			i;
	int			j;

	tmp_r = data.start_room;
	tmp_n = tmp_r->neighbor;
	nb_path = 0;
	j = 0;
	while (tmp_n != NULL)
	{
		if (tmp_n->flow == 1)
			nb_path++;
		tmp_n = tmp_n->next;
	}
	while (all_path[j] != 0)
		j++;
	all_path[j] = (t_path**)malloc(sizeof(t_path*) * (nb_path + 1));
	all_path[j][nb_path] = 0;
	tmp_n = tmp_r->neighbor;
	i = 0;
	while (i < nb_path)
	{
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		len = ft_path_len(tmp_n->room, data);
		all_path[j][i] = ft_fill_path(all_path[j][i], tmp_n->room, len, data);
		tmp_n = tmp_n->next;
		i++;
	}
	return (all_path);
}

void	ft_print_paths(t_path ***all_path)
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
			k = 0;
			ft_printf("\nPath n*%d :", j + 1);
			while (all_path[i][j]->path[k] != 0)
			{
				ft_printf(" %s -", all_path[i][j]->path[k]->name);
				k++;
			}
			j++;
		}
		i++;
		ft_printf("\n\n");
	}
}
