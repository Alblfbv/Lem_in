/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 15:21:07 by allefebv          #+#    #+#             */
/*   Updated: 2019/05/01 22:34:15 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_init_ants(t_ant *ants, t_data data)
{
	int	i;

	i = 0;
	while (i < data.nb_ants)
	{
		ants[i].name = i + 1;
		ants[i].flag = 0;
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
			if (j != 0)
				path[i]->path[j]->source = path[i]->path[j - 1];
			j++;
		}
		i++;
	}
}

void	ft_start_end(t_ant *ants, t_data data)
{
	int	i;

	i = 0;
	while (data.nb_ants)
	{
		ft_printf("L%d-%s", ants[i], data.end_room->name);
		data.nb_ants--;
		i++;
		if (data.nb_ants)
			write(1, " ", 1);
	}
}

void	ft_ants_move(t_ant *ants, t_path **path, t_data data)
{
	int	remaining_ants;
	t_room	*tmp;
	int	i;
	int	j;
	int	flag;

	remaining_ants = data.nb_ants;
	j = 0;
	while (remaining_ants)
	{
		i = 0;
		flag = 0;
		while (path[i] != 0)
		{
			tmp = path[i]->end;
			while (tmp != path[i]->path[0])
			{
				if (tmp->ant != NULL)
				{
					if (tmp == path[i]->end)
						remaining_ants--;
					if (flag == 1)
					{
						write(1, " ", 1);
						flag = 0;
					}
					ft_printf("L%d-%s", tmp->ant->name, tmp->next->name);
					if (path[i]->ants != 0 || (tmp != path[i]->path[1] && tmp->source->ant != NULL))
						ft_printf(" ");
					else
						flag = 1;
					tmp->next->ant = tmp->ant;
					tmp->ant = tmp->source->ant;
				}
				tmp = tmp->source;
			}
			tmp = path[i]->path[1];
			if (path[i]->ants != 0)
			{
				ants[j].flag = 0;
				tmp->ant = ants + j;
				ft_printf("L%d-%s", tmp->ant->name, tmp->name);
				if (path[i + 1] != 0 && path[i + 1]->ants != 0)
					write(1, " ", 1);
				else
					flag = 1;
				path[i]->ants--;
				j++;
			}
			i++;
		}
		ft_printf("\n");
	}
	if (data.flag_print == 1)
		ft_printf("\n\nMap solved in %d steps\n", j);
}

void	ft_ants_manage(t_path **path, t_data data)
{
	t_ant	*ants;

	//ft_printf("%s", ((*path)->path[2]->name));
	ants = (t_ant*)malloc(sizeof(t_ant) * data.nb_ants);
	ft_init_ants(ants, data);
	ft_init_paths(path);
	if (!path[1] && path[0]->path[2] == 0)
		ft_start_end(ants, data);
	else
		ft_ants_move(ants, path, data);
	free(ants);
}
