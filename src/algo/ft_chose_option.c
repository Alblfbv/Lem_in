/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chose_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:41:09 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/23 21:41:38 by allefebv         ###   ########.fr       */
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

void		ft_neg_lems(t_path **path, int *flag, int *nb_path, int *sum_len)
{
	int	i;

	i = 0;
	*sum_len = *sum_len - path[i]->length;
	free(path[i]);
	path[i] = path[i + 1];
	while (path[i] != 0)
	{
		path[i] = path[i + 1];
		i++;
	}
	*flag = 0;
	*nb_path = *nb_path - 1;
}

void		ft_compute_nb_lem(t_path **path, t_data data)
{
	int	nb_path;
	int	sum_len;
	int	flag;
	int	unplaced_lems;
	int	i;

	nb_path = 0;
	sum_len = 0;
	while (path[nb_path] != 0)
	{
		sum_len = sum_len + path[nb_path]->length;
		nb_path++;
	}
	flag = 0;
	while (flag == 0)
	{
		i = 0;
		flag = 1;
		unplaced_lems = data.nb_lem;
		while (i < nb_path && flag == 1)
		{
			path[i]->lems = (data.nb_lem + sum_len - (nb_path * path[i]->length)) / nb_path;
			if (path[i]->lems <= 0)
				ft_neg_lems(path + i, &flag, &nb_path, &sum_len);
			else
			{
				unplaced_lems = unplaced_lems - path[i]->lems;
				path[i]->steps = path[i]->lems + path[i]->length - 1;
				i++;
			}
		}
	}
	ft_place_remaining_lems(unplaced_lems, path);
	i = 0;
	while (path[i] != 0)
	{
		//ft_printf("steps = %d nb_lem = %d\n", path[i]->steps, path[i]->lems);
		i++;
	}
}

t_path	**ft_chose_best_path(t_path ***all_path, t_data data)
{
	int	i;
	int	smallest_steps;
	int	pos_small;

	i = 0;
	while (all_path[i] != 0)
	{
		ft_compute_nb_lem(all_path[i], data);
		i++;
	}
	i = 0;
	//TEMPORAIRE
	smallest_steps = all_path[i][0]->steps;
	pos_small = 0;
	while (all_path[i] != 0)
	{
		//TEMPORAIRE
		if (smallest_steps > all_path[i][0]->steps)
		{
			//TEMPORAIRE
			smallest_steps = all_path[i][0]->steps;
			pos_small = i;
		}
		i++;
	}
	return (all_path[pos_small]);
}
