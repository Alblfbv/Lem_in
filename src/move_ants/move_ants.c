/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:21:07 by allefebv          #+#    #+#             */
/*   Updated: 2019/05/01 19:51:44 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_init_ants(t_ants *ants, t_data data, t_path **path)
{
	int	i;

	i = 0;
	while (i < data.nb_ants)
	{
		ants[i].name = i + 1;
		ants[i].room = data.start_room;
		i++;
	}
}

void	ft_init_paths(t_path **path)
{
	int	i;
	int	j;

	i = 0;
	while (path[i] != 0)
	{
		j = 0;
		while (path[i]->path[j] != 0)
		{
			path[i]->path[j]->next = path[i]->path[j + 1];
			j++;
		}
		i++;
	}
}

void	ft_ants_move(t_ant *ants, t_path **path, t_data data)
{
	int	remaining_ants;
	t_room	*tmp_r;
	int	i;
	int	j;

	remaining_ants = data.nb_ants;
	while (remaining_ants)
	{
		while (path[i] != 0)
		{
			if (path[i]->ants != 0)
			{
				tmp_r = path[i]->end;
				while (tmp_r != data.start_room)
				{
					ft_printf("")
					tmp_r->ant = tmp_r->source->ant
					tmp_r = tmp_r->source;
				}
				while (ants[j]->room != data.start_room)
					i++;
				ants[j]->room = path[i]->path[0];
				path[i]->path[0]->ant = ants[j];
				path[i]->ants--;
				remaining_ants--;
			}
		}
	}
	if (data.flag_print == 1)
		ft_printf("\n\nMap solved in %d steps\n", j);
}

void	ft_ants_manage(t_path **path, t_data data)
{
	t_ants	*ants;

	//ft_printf("%s", ((*path)->path[2]->name));
	ants = (t_ants*)malloc(sizeof(t_ants) * data.nb_ants);
	ft_init_ants(ants, data, path);
	ft_init_paths(path);
	ft_ants_move(ants, path, data);
	free(ants);
}
