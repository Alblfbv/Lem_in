/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chose_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:41:09 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/22 13:59:58 by allefebv         ###   ########.fr       */
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

void		ft_compute_nb_lem(t_path **path, t_lem lem)
{
	int	nb_path;
	int	sum_len;
	int	unplaced_lems;
	int	i;

	nb_path = 0;
	sum_len = 0;
	unplaced_lems = lem.nb_lem;
	while (path[nb_path] != 0)
	{
		sum_len = sum_len + path[nb_path]->length;
		nb_path++;
	}
	i = 0;
	while (i < nb_path)
	{
		path[i]->lems = (lem.nb_lem + sum_len - (nb_path * path[i]->length)) / nb_path;
		unplaced_lems = unplaced_lems - path[i]->lems;
		path[i]->steps = path[i]->lems + path[i]->length - 1;
		i++;
	}
	ft_place_remaining_lems(unplaced_lems, path);
	i = 0;
	while (path[i] != 0)
	{
		ft_printf("steps = %d nb_lem = %d\n", path[i]->steps, path[i]->lems);
		i++;
	}
}

void	ft_chose_best_path(t_path ***all_path, t_lem lem)
{
	int	i;

	i = 0;
	while (all_path[i] != 0)
	{
		ft_compute_nb_lem(all_path[i], lem);
		i++;
	}

}
