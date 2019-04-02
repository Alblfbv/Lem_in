/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 15:24:35 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	parser(t_lem *lem, t_room *room)
{
	char	*line;
	int		flag;
	int		check;

	flag = 0;
	while ((get_next_line(0, &line)) == 1 && check == 0)
	{
		check = 0;
		if (ft_comment(line) == 1)
			check = 1;
		if (ft_lem(line, lem) == 1 && flag == 0)
		{
			flag = 1;
			check = 1;
		}
		if (ft_command(line, lem, room) == 1)
			check = 1;
/*		if (ft_room(line) == 1 && flag == 1)
			check = 1;
		if (ft_road(line) == 1)
		{
			ft_store_road(lem, line);
			flag = 2;
		}*/
		ft_printf("%s\n", line);
		free(line);
	}
	if (check == 0)
	{
		while ((get_next_line(0, &line)) == 1)
			ft_printf("%s\n", line);
		ft_printf("\nError\n");
		return ;
	}
	ft_printf("\n");
}
