/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/25 14:41:54 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_error(t_data *data, char *line, t_coord **coord_tab)
{
	free(line);
	free(coord_tab);
	if (data->nb_lem == 0)
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

int			parser(t_data *data, t_room **room)
{
	char	*line;
	int		flag;
	int		check;
	t_coord	**coord_tab;

	flag = 0;
	check = 1;
	ft_init_coord_tab(&coord_tab);
	while ((get_next_line(0, &line)) == 1 && check == 1)
	{
		ft_lstadd_end(data->instructions,
				ft_lstnew(line, sizeof(char) * ((ft_strlen(line) + 1))));
		check = 0;
		if (!flag && ft_lem(line, data, &flag))
			check = 1;
		else if (flag && flag != 2 && ft_room(line, room, data, flag))
		{
			check = 1;
			flag = 1;
			data->nb_room++;
		}
		else if ((flag) && (ft_comment(line) || ft_command(line, &flag)))
			check = 1;
		else if ((flag == 1 || flag == 2) && ft_path(line, room))
		{
			flag = 2;
			check = 1;
		}
		free(line);
	}
	return (ft_error(data, line, coord_tab));
}
