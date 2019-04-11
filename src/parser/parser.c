/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/11 17:36:10 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_error(int check, char *line)
{
	if (check == 0)
	{
		while ((get_next_line(0, &line)) == 1)
		{
			ft_printf("Error = %s\n", line);
			free(line);
		}
		ft_strdel(&line);
		ft_printf("\nError\n");
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
	ft_init_coord_tab(&coord_tab);
	while ((get_next_line(0, &line)) == 1 && check == 1)
	{
		check = 0;
		ft_printf("%s\n", line);
		if ((flag == 1 || flag == 2)
			&& (ft_comment(line) == 1
				|| ft_command(line, lem, room, flag) == 1))
			check = 1;
		if (flag == 0 && ft_lem(line, lem, &flag) == 1)
			check = 1;
		if ((flag == 1 || flag == 2)
			&& ft_room(line, room, lem, 'M') == 1 && flag == 1)
		{
			if (ft_check_coord(line, coord_tab))
				check = 1;
			i++;
		}
		if ((flag == 1 || flag == 2) && ft_path(line, room) == 1)
		{
			flag = 2;
			check = 1;
		}
		free(line);
	}
	lem->nb_room = i + 2;
	free(line);
	return (ft_error(check, line));
}
