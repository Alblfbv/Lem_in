/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/05 14:53:30 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_error(int check, char *line)
{
	if (check == 0)
	{
		while ((get_next_line(0, &line)) == 1)
		{
			ft_printf("Error = %s\n", line);
			free(line);
		}
		ft_strdel(&line);
		ft_printf("\nError\n");
		return (0);
	}
	return (1);
}

int			parser(t_lem *lem, t_room **room)
{
	char	*line;
	int		flag;
	int		check;

	flag = 0;
	check = 1;
	while ((get_next_line(0, &line)) == 1 && check == 1)
	{
		check = 0;
		ft_printf("%s\n", line);
		if (ft_comment(line) == 1 || ft_command(line, lem, room, flag) == 1)
			check = 1;
		if (flag == 0 && ft_lem(line, lem, &flag) == 1)
			check = 1;
		if (ft_room(line, room, lem, 'M') == 1 && flag == 1)
			check = 1;
		if (ft_path(line, room) == 1)
		{
			flag = 2;
			check = 1;
		}
		free(line);
	}
	free(line);
	return (ft_error(check, line));
}
