/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 11:55:12 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	parser(t_lem *lem)
{
	char	*line;
	int		flag;
	int		check;
	int		i;

	flag = 0;
	i = 0;
	while ((get_next_line(0, &line)) == 1)
	{
		check = 0;
		if (ft_check_lem(line) == 1 && flag == 0)
		{
			ft_store_lem(lem, line);
			flag = 1;
			check = 1;
		}
/*		if (ft_check_room(line) == 1 && flag == 1)
		{
			ft_store_room(lem, line);
		}
		if (ft_check_road(line) == 1)
		{
			ft_store_road(lem, line);
			flag = 2;
		}*/
		ft_printf("%s\n", line);
		free(line);
		if (check == 0)
			break;
	}
	if (check == 0)
	{
		while ((get_next_line(0, &line)) == 1)
			ft_printf("%s\n", line);
		ft_printf("Error\n");
	}
}
