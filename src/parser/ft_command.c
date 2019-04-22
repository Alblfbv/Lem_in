/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:48:45 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/22 15:42:42 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_store_start(t_data *data, t_room **room)
{
	data->j = data->j + 1;
	if (!(ft_room(data->result_read[data->j], room, data, 'S')))
		return (0);
	return (1);
}

static int		ft_store_end(t_data *data, t_room **room)
{
	data->j = data->j + 1;
	if (!(ft_room(data->result_read[data->j], room, data, 'E')))
		return (0);
	return (1);
}

int				ft_command(char *line, t_data *data, t_room **room, int flag)
{
	int		i;

	i = ft_strlen(line);
	if (i < 2)
		return (0);
	if (ft_strequ(line, "##start") == 1)
	{
		if ((ft_store_start(data, room)) == 0 && flag != 1)
			return (0);
		return (1);
	}
	if (ft_strequ(line, "##end") == 1)
	{
		if ((ft_store_end(data, room)) == 0 && flag != 1)
			return (0);
		return (1);
	}
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}
