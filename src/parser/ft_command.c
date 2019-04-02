/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:48:45 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 17:00:48 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_store_start(t_lem *lem, t_room *room)
{
	char	*line;

	get_next_line(0, &line);
	ft_room(line, room);
}

static void		ft_store_end(t_lem *lem, t_room *room)
{
	char	*line;

	get_next_line(0, &line);
	ft_room(line, room);
}

int				ft_command(char *line, t_lem *lem, t_room *room)
{
	int		i;

	i = ft_strlen(line);
	if (i < 2)
		return (0);
	if (ft_strequ(line, "##start") == 1)
	{
//		ft_store_start();
		return (1);
	}
	if (ft_strequ(line, "##end") == 1)
	{
//		ft_store_end();
		return (1);
	}
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}
