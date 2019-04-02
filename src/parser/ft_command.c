/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:48:45 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 15:16:59 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_command(char *line)
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
