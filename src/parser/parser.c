/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/03 14:39:36 by jfleury          ###   ########.fr       */
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
		if (ft_comment(line) == 1)
		{
			ft_printf("ft_comment GNL N_%d / Check = 1\n", i);
			check = 1;
		}
		if (flag == 0 && ft_lem(line, lem, &flag) == 1)
		{
			ft_printf("ft_comment GNL N_%d / Check = 1\n", i);
			check = 1;
		}
/*		if (ft_command(line, lem, room) == 1)
		{
			ft_printf("ft_comment GNL N_%d / Check = 1\n", i);
			check = 1;
		}*/
		if (ft_room(line, room) == 1 && flag == 1)
		{
			ft_printf("ft_room GNL N_%d / Check = 1\n", i);
			check = 1;
		}
		/*
		if (ft_path(line) == 1)
			flag = 2;
		*/
		ft_printf("%s\n", line);
		free(line);
		i++;
	}
	if (check == 0)
	{
		while ((get_next_line(0, &line)) == 1)
			ft_printf("Error = %s\n", line);
		ft_printf("\nError\n");
		return ;
	}
	ft_printf("\n");
}
