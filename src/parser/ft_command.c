/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:48:45 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/04 13:22:28 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		ft_store_start(t_lem *lem, t_room **room)
{
	char	*line;

	(void)lem;
	get_next_line(0, &line);
	ft_room(line, room, lem, 'S');
	ft_printf("%s\n", line);
	free(line);
}

static void		ft_store_end(t_lem *lem, t_room **room)
{
	char	*line;

	(void)lem;
	get_next_line(0, &line);
	ft_room(line, room, lem, 'E');
	ft_printf("%s\n", line);
	free(line);
}

int				ft_command(char *line, t_lem *lem, t_room **room)
{
	int		i;

	(void)lem;
	i = ft_strlen(line);
	if (i < 2)
		return (0);
	if (ft_strequ(line, "##start") == 1)
	{
		ft_store_start(lem, room);
		return (1);
	}
	if (ft_strequ(line, "##end") == 1)
	{
		ft_store_end(lem, room);
		return (1);
	}
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}
