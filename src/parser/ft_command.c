/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:48:45 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/12 09:58:43 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_store_start(t_lem *lem, t_room **room)
{
	lem->j = lem->j + 1;
	if (!(ft_room(lem->result_read[lem->j], room, lem, 'S')))
		return (0);
	return (1);
}

static int		ft_store_end(t_lem *lem, t_room **room)
{
	lem->j = lem->j + 1;
	if (!(ft_room(lem->result_read[lem->j], room, lem, 'E')))
		return (0);
	return (1);
}

int				ft_command(char *line, t_lem *lem, t_room **room, int flag)
{
	int		i;

	(void)lem;
	i = ft_strlen(line);
	if (i < 2)
		return (0);
	if (ft_strequ(line, "##start") == 1)
	{
		if ((ft_store_start(lem, room)) == 0 && flag != 1)
			return (0);
		return (1);
	}
	if (ft_strequ(line, "##end") == 1)
	{
		if ((ft_store_end(lem, room)) == 0 && flag != 1)
			return (0);
		return (1);
	}
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}
