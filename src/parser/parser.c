/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/22 15:45:49 by allefebv         ###   ########.fr       */
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

int			parser(t_data *data, t_room **room)
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
	data->j = 0;
	ft_init_coord_tab(&coord_tab);
	data->tmp = ft_strnew(1);
	while ((get_next_line(0, &line)) == 1 && check == 1)
	{
		data->tmp = ft_strextend(data->tmp, line);
		data->tmp = ft_strextend(data->tmp, "\n");
		free(line);
	}
	data->result_read = ft_strsplit(data->tmp, '\n');
	free(data->tmp);
	while (data->result_read[data->j] != 0 && check == 1)
	{
		check = 0;
		if ((flag == 1 || flag == 2) && (ft_comment(data->result_read[data->j]) == 1 || ft_command(data->result_read[data->j], data, room, flag) == 1))
			check = 1;
		if (flag == 0 && ft_lem(data->result_read[data->j], data, &flag) == 1)
			check = 1;
		if ((flag == 1 || flag == 2) && ft_room(data->result_read[data->j], room, data, 'M') == 1 && flag == 1)
		{
			if (ft_check_coord(data->result_read[data->j], coord_tab))
				check = 1;
			i++;
		}
		if ((flag == 1 || flag == 2) && ft_path(data->result_read[data->j], room) == 1)
		{
			flag = 2;
			check = 1;
		}
		data->j++;
	}
	data->nb_room = i + 2;
	return (ft_error(check));
}
