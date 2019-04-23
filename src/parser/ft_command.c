/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:48:45 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/23 16:47:36 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*static int		ft_store_start(t_data *data, t_room **room, char *line)
{
	if (!(ft_room((char*)(*tmp)->content, room, data, 'S')))
		return (0);
	return (1);
}

static int		ft_store_end(t_data *data, t_room **room, char *line)
{
	if (!(ft_room((char*)(*tmp)->content, room, data, 'E')))
		return (0);
	return (1);
}
*/

int				ft_command(char *line, int *flag)
{
	int		i;

	i = ft_strlen(line);
	if (i < 2)
		return (0);
	if (ft_strequ(line, "##start") && *flag != 0)
	{
		*flag = 3;
		return (1);
		/*if (!ft_store_start(data, room, tmp))
			return (0);
		return (1); */
	}
	if (ft_strequ(line, "##end") && *flag != 0)
	{
		*flag = 4;
		return (1);
		/*if (!ft_store_end(data, room, tmp))
			return (0);
		return (1); */
	}
	if (line[0] == '#' && line[1] == '#')
		return (1);
	return (0);
}
