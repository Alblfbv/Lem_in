/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chose_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:41:09 by allefebv          #+#    #+#             */
/*   Updated: 2019/05/02 16:54:22 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_place_remaining_ants(int unplaced_ants, t_path **path)
{
	int	i;
	int	smaller_steps;
	int	pos_min;

	while (unplaced_ants)
	{
		i = 0;
		smaller_steps = path[i]->steps;
		pos_min = i;
		while (path[i] != 0)
		{
			if (smaller_steps > path[i]->steps)
			{
				smaller_steps = path[i]->steps;
				pos_min = i;
			}
			i++;
		}
		path[pos_min]->steps++;
		path[pos_min]->ants++;
		unplaced_ants--;
	}
}

static void	ft_neg_ants(t_path **path, t_dispatch *dis)
{
	int	i;

	i = 0;
	dis->sum_len = dis->sum_len - path[i]->length;
	free(path[i]);
	path[i] = path[i + 1];
	while (path[i] != 0)
	{
		path[i] = path[i + 1];
		i++;
	}
	dis->flag = 0;
	dis->nb_path = dis->nb_path - 1;
}

static void	ft_compute_nb_ants2(t_dispatch *dis, t_path **path, t_data data)
{
	int	i;

	i = 0;
	dis->flag = 1;
	dis->unplaced_ants = data.nb_ants;
	while (i < dis->nb_path && dis->flag == 1)
	{
		path[i]->ants = (data.nb_ants + dis->sum_len
				- (dis->nb_path * path[i]->length)) / dis->nb_path;
		if (path[i]->ants <= 0)
			ft_neg_ants(path + i, dis);
		else
		{
			dis->unplaced_ants = dis->unplaced_ants - path[i]->ants;
			path[i]->steps = path[i]->ants + path[i]->length - 1;
			i++;
		}
	}
}

static void	ft_compute_nb_ants(t_path **path, t_data data, int *pos_small)
{
	t_dispatch	dis;

	*pos_small = 0;
	dis.nb_path = 0;
	dis.sum_len = 0;
	while (path[dis.nb_path] != 0)
	{
		dis.sum_len = dis.sum_len + path[dis.nb_path]->length;
		dis.nb_path++;
	}
	dis.flag = 0;
	while (dis.flag == 0)
		ft_compute_nb_ants2(&dis, path, data);
	ft_place_remaining_ants(dis.unplaced_ants, path);
}

t_path		**ft_chose_best_path(t_path ***all_path, t_data data)
{
	int	i;
	int	j;
	int	smallest_steps;
	int	pos_small;

	i = -1;
	if (all_path[0][0]->path[1] == data.end_room)
		return (all_path[0]);
	while (all_path[++i] != 0)
		ft_compute_nb_ants(all_path[i], data, &pos_small);
	smallest_steps = all_path[0][0]->steps;
	i = -1;
	while (all_path[++i] != 0)
	{
		j = -1;
		while (all_path[i][++j] != 0)
		{
			if (smallest_steps > all_path[i][j]->steps)
			{
				smallest_steps = all_path[i][j]->steps;
				pos_small = i;
			}
		}
	}
	return (all_path[pos_small]);
}
