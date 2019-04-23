/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_lems.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:21:07 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/23 11:49:07 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_init_lem_tab(t_lems *lems, t_data data, t_path **path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data.nb_lem)
	{
		lems[i].name = i + 1;
		lems[i].path = path[j];
		lems[i].room = data.start_room;
		path[j]->lems--;
		j++;
		i++;
		if (path[j] == 0)
			j = 0;
		while (i < data.nb_lem && path[j]->lems == 0)
		{
			j++;
			if (path[j] == 0)
				j = 0;
		}
	}
}

void	ft_lem_move(t_lems *lems, int nb_path, t_data data)
{
	int	allowed_movements;
	int	i;
	int	cpy;

	allowed_movements = nb_path;
	i = 0;
	while (allowed_movements)
	{
		cpy = allowed_movements;
		i = 0;
		while (cpy && i < data.nb_lem)
		{
			while (lems[i].room == data.end_room)
				i++;
			if (lems[i].room == data.start_room)
			{
				lems[i].room = (lems[i].path)->path[1];
				ft_printf("L%d-%s", lems[i].name, lems[i].room->name);
				if (lems[i].room == data.end_room && lems[i].path->length != 1)
					allowed_movements--;
				else if (lems[i].path->length == 1 && i == data.nb_lem - 1)
					allowed_movements--;
				else if (lems[i].path->length != 1 && allowed_movements < data.nb_lem && i < data.nb_lem - nb_path)
					allowed_movements++;
			}
			else
			{
				lems[i].room = lems[i].room->next;
				ft_printf("L%d-%s", lems[i].name, lems[i].room->name);
				if (lems[i].room == data.end_room)
					allowed_movements--;
				if (allowed_movements != 0)
					ft_printf(" ");
			}
			cpy--;
			i++;
		}
		ft_printf("\n");
	}
}

void	ft_lem_manage(t_path **path, t_data data)
{
	t_lems	*lems;
	int		nb_path;

	nb_path = 0;
	lems = (t_lems*)malloc(sizeof(t_lems) * data.nb_lem);
	while (path[nb_path] != 0)
		nb_path++;
	ft_init_lem_tab(lems, data, path);
	ft_lem_move(lems, nb_path, data);
}
