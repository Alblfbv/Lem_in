/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chose_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 16:41:09 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/19 17:56:12 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_place_remaining_lems(int unplaced_lems, int *steps, int *nb_lem_path)
{
	int	i;
	int	smaller_steps;
	int	pos_min;

	while (unplaced_lems)
	{
		i = 0;
		smaller_steps = steps[i];
		pos_min = i;
		while (steps[i] != 0)
		{
			if (smaller_steps > steps[i])
			{
				smaller_steps = steps[i];
				pos_min = i;
			}
			i++;
		}
		steps[pos_min]++;
		nb_lem_path[pos_min]++;
		unplaced_lems--;
	}
}

static void	ft_steps(int *tab, t_lem lem, int *nb_lem_path, int *steps, int nb_path, int sum_len)
{
	int	i;
	int	unplaced_lems;

		steps[nb_path] = 0;
	i = 0;
	unplaced_lems = lem.nb_lem;
	while (tab[i] != 0)
	{
		nb_lem_path[i] = (lem.nb_lem + sum_len - (nb_path * tab[i])) / nb_path;
		unplaced_lems = unplaced_lems - nb_lem_path[i];
		steps[i] = nb_lem_path[i] + tab[i] - 1;
		i++;
	}
	ft_place_remaining_lems(unplaced_lems, steps, nb_lem_path);
}

void		ft_compute_nb_lem(int *tab, t_lem lem)
{
	int	nb_path;
	int	sum_len;
	int	*nb_lem_path;
	int	*steps;
	int	i;

	nb_path = 0;
	sum_len = 0;
	while (tab[nb_path] != 0)
	{
		sum_len = sum_len + tab[nb_path];
		nb_path++;
	}
	nb_lem_path = (int*)malloc(sizeof(int) * (nb_path + 1));
	steps = (int*)malloc(sizeof(int) * (nb_path + 1));
	ft_steps(tab, lem, nb_lem_path, steps, nb_path, sum_len);
	i = 0;
	while (steps[i] != 0)
	{
		ft_printf("steps = %d nb_lem = %d\n", steps[i], nb_lem_path[i]);
		i++;
	}
}

void	ft_chose_best_path(t_room ****all_path, t_lem lem)
{
	int	**tab;
	int	i;

	tab = ft_create_path_tab(all_path);
	i = 0;
	while (tab[i] != 0)
	{
		ft_compute_nb_lem(tab[i], lem);
		i++;
	}

}

