/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/04 14:35:26 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	parser(t_lem *lem, t_room **room)
{
	char	*line;
	int		flag;
	int		check;
	int		i;

	flag = 0;
	check = 1;
	i = 0;
	(void)lem;

	while ((get_next_line(0, &line)) == 1 && check == 1)
	{
		check = 0;
		ft_printf("%s\n", line);
		if (ft_comment(line) == 1)
		{
			ft_printf("GNL N_%d / ft_comment\n\n", i);
			check = 1;
		}
		if (flag == 0 && ft_lem(line, lem, &flag) == 1)
		{
			ft_printf("GNL N_%d / ft_lem\n\n", i);
			check = 1;
		}
		if (ft_command(line, lem, room) == 1)
		{
			ft_printf("GNL N_%d / ft_command\n\n", i);
			check = 1;
		}
		if (ft_room(line, room, lem, 'M') == 1 && flag == 1)
		{
			ft_printf("GNL N_%d ft_room\n\n", i);
			check = 1;
		}
		if (ft_path(line, room) == 1)
		{
			ft_printf("GNL N_%d ft_path\n\n", i);
			flag = 2;
			check = 1;
		}
		free(line);
		i++;
	}
	free(line);
	if (check == 0)
	{
		while ((get_next_line(0, &line)) == 1)
		{
			ft_printf("Error = %s\n", line);
			free(line);
		}
		ft_strdel(&line);
		ft_printf("\nError\n");
		return ;
	}
	ft_printf("\n");
}
