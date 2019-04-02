/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:32:11 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 17:54:37 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_lem	lem;
	t_room	**room;
	int		i;
	t_room	*tmp;
	int		key;

	i = 0;
	room = (t_room**)malloc(sizeof(t_room*) * HASH_TAB);
	while (i < HASH_TAB)
	{
		room[i] = NULL;
		i++;
	}
	parser(&lem, room);

	key = ft_hash("1", HASH_TAB);
	tmp = room[key];
	while (tmp != NULL)
	{
		ft_printf("s1 = %s\n", tmp->name);
		tmp = tmp->next;
	}

	key = ft_hash("2", HASH_TAB);
	tmp = room[key];
	while (tmp != NULL)
	{
		ft_printf("s2 = %s\n", tmp->name);
		tmp = tmp->next;
	}

	key = ft_hash("jkhfdsf", HASH_TAB);
	tmp = room[key];
	while (tmp != NULL)
	{
		ft_printf("s3 = %s\n", tmp->name);
		tmp = tmp->next;
	}

	key = ft_hash("!@#", HASH_TAB);
	tmp = room[key];
	while (tmp != NULL)
	{
		ft_printf("s4 = %s\n", tmp->name);
		tmp = tmp->next;
	}
}
