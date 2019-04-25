/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chose_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:41:09 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/25 19:25:26 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_place_remaining_lems(int unplaced_lems, t_path **path)
{
	int	i;
	int	smaller_steps;
	int	pos_min;

	while (unplaced_lems)
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
		path[pos_min]->lems++;
		unplaced_lems--;
	}
}

static void	ft_neg_lems(t_path **path, t_dispatch *dis)
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

static void	ft_compute_nb_lem2(t_dispatch *dis, t_path **path, t_data data)
{
	int	i;

	i = 0;
	dis->flag = 1;
	dis->unplaced_lems = data.nb_lem;
	while (i < dis->nb_path && dis->flag == 1)
	{
		path[i]->lems = (data.nb_lem + dis->sum_len
				- (dis->nb_path * path[i]->length)) / dis->nb_path;
		if (path[i]->lems <= 0)
			ft_neg_lems(path + i, dis);
		else
		{
			dis->unplaced_lems = dis->unplaced_lems - path[i]->lems;
			path[i]->steps = path[i]->lems + path[i]->length - 1;
			i++;
		}
	}
}

static void	ft_compute_nb_lem(t_path **path, t_data data)
{
	t_dispatch	dis;

	dis.nb_path = 0;
	dis.sum_len = 0;
	while (path[dis.nb_path] != 0)
	{
		dis.sum_len = dis.sum_len + path[dis.nb_path]->length;
		dis.nb_path++;
	}
	dis.flag = 0;
	while (dis.flag == 0)
		ft_compute_nb_lem2(&dis, path, data);
	ft_place_remaining_lems(dis.unplaced_lems, path);
}

t_path		**ft_chose_best_path(t_path ***all_path, t_data data)
{
	int	i;
	int	j;
	int	smallest_steps;
	int	pos_small;

	i = -1;
	while (all_path[++i] != 0)
		ft_compute_nb_lem(all_path[i], data);
	pos_small = 0;
	i = -1;
	smallest_steps = all_path[i + 1][0]->steps;
	while (all_path[++i] != 0)
	{
		j = 0;
		while (all_path[i][j] != 0)
		{
			if (smallest_steps > all_path[i][j]->steps)
			{
				smallest_steps = all_path[i][j]->steps;
				pos_small = i;
			}
			j++;
		}
	}
	return (all_path[pos_small]);
}
