/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/12 11:38:25 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_error(int check)
{
	if (check == 0)
	{
		ft_printf("Error\n");
		return (0);
	}
	return (1);
}

int			ft_init_coord_tab(t_coord ***coord_tab)
{
	int	i;

	i = 0;
	if (!(*coord_tab = (t_coord**)malloc(sizeof(t_coord*) * HASH_TAB)))
		return (0);
	while (i < HASH_TAB)
	{
		(*coord_tab)[i] = NULL;
		i++;
	}
	return (1);
}

int			parser(t_lem *lem, t_room **room)
{
	char	*line;
	int		flag;
	int		flag_lem;
	int		check;
	int		i;
	t_coord	**coord_tab;

	flag = 0;
	flag_lem = 0;
	check = 1;
	i = 0;
	lem->j = 0;
	ft_init_coord_tab(&coord_tab);
	lem->tmp = ft_strnew(1);
	while ((get_next_line(0, &line)) == 1 && check == 1)
	{
		lem->tmp = ft_strextend(lem->tmp, line);
		lem->tmp = ft_strextend(lem->tmp, "\n");
		free(line);
	}
	lem->result_read = ft_strsplit(lem->tmp, '\n');
	free(lem->tmp);
	while (lem->result_read[lem->j] != 0)
	{
		check = 0;
		if ((flag == 1 || flag == 2) && (ft_comment(lem->result_read[lem->j]) == 1 || ft_command(lem->result_read[lem->j], lem, room, flag) == 1))
			check = 1;
		if (flag == 0 && ft_lem(lem->result_read[lem->j], lem, &flag) == 1)
			check = 1;
		if ((flag == 1 || flag == 2) && ft_room(lem->result_read[lem->j], room, lem, 'M') == 1 && flag == 1)
		{
			if (ft_check_coord(lem->result_read[lem->j], coord_tab))
				check = 1;
			i++;
		}
		if ((flag == 1 || flag == 2) && ft_path(lem->result_read[lem->j], room) == 1)
		{
			flag = 2;
			check = 1;
		}
		lem->j++;
	}
	lem->nb_room = i + 2;
	return (ft_error(check));
}
