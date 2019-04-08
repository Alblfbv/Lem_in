/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_coord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:44:21 by allefebv          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/04 16:47:57 by allefebv         ###   ########.fr       */
=======
/*   Updated: 2019/04/05 18:41:14 by jfleury          ###   ########.fr       */
>>>>>>> c5dd4de90721318ef833f3d583378d117da51aa0
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_check_coord(char *line, t_coord **coord_tab)
{
	int		key;
	t_coord	*tmp;
	int		x;
	int		y;
	char	**split;

	key = ft_hash(ft_itoa(x), HASH_TAB);
	tmp = coord_tab[key];
	split = ft_strsplit(line, ' ');
	x = ft_atoi(split[1]);
	y = ft_atoi(split[2]);
	if (coord_tab[key] == NULL)
	{
		if(!(coord_tab[key] = (t_coord*)malloc(sizeof(t_coord))))
			return (0);
		(*(coord_tab + key))->x = x;
		(*(coord_tab + key))->y = y;
		(coord_tab[key])->next = NULL;
	}
	else
	{
		if (tmp[key].x == x && tmp[key].y == y)
			return (0);
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
			if (tmp[key].x == x && tmp[key].y == y)
				return (0);
		}
		if(!(tmp->next = (t_coord*)malloc(sizeof(t_coord))))
			return (0);
		tmp->next->x = x;
		tmp->next->y = y;
		tmp->next->next = NULL;
	}
	return (1);
}
