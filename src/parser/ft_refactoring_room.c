/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refactoring_room.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:01:49 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/09 17:04:31 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_init_final_room(t_room ***room, int size)
{
	int		i;

	i = 0;
	if (!(*room = (t_room**)malloc(sizeof(t_room*) * size)))
		return (0);
	while (i < size)
	{
		(*room)[i] = NULL;
		i++;
	}
	return (1);
}

int		ft_refactoring_room(t_room **room, t_lem *lem, t_room **final_room)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_init_final_room(&final_room, lem->nb_room);
	while (i < HASH_TAB)
	{
		while (room[i] == NULL)
		{
			printf("Null = %d\n", i);
			i++;
		}
		final_room[j] = room[i];
		j++;
		while (room[i]->next != NULL)
		{
			final_room[j] = room[i];
			room[i] = room[i]->next;
			j++;
		}
		i++;
	}
}
