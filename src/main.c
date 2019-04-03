/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:32:11 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/03 18:58:31 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_clean(t_room **room)
{
	int			i;
	t_neighbor	*tmp_n;
	t_neighbor	*tmp_n_nxt;
	t_room		*tmp_r;
	t_room		*tmp_r_nxt;

	i = 0;
	while (i < HASH_TAB)
	{
		if (room[i] != NULL)
		{
			tmp_r = room[i];
			while (tmp_r != NULL)
			{
				tmp_n = tmp_r->neighbor;
				while (tmp_n != NULL)
				{
					tmp_n_nxt = tmp_n->next;
					free(tmp_n);
					tmp_n = tmp_n_nxt;
				}
				free(tmp_r->name);
				tmp_r_nxt = tmp_r->next;
				free(tmp_r);
				tmp_r = tmp_r_nxt;
			}
		}
		i++;
	}
	free(room);
	return (0);
}

int		main(void)
{
	t_lem	lem;
	t_room	**room;
	int		i;
//	t_room	*tmp;
//	int		key;

	i = 0;
	room = (t_room**)malloc(sizeof(t_room*) * HASH_TAB);
	while (i < HASH_TAB)
	{
		room[i] = NULL;
		i++;
	}
	parser(&lem, room);

	i = ft_hash("996", HASH_TAB);
	ft_printf("%d\n", i);
	ft_printf("%p\n", room[i]->neighbor);
	ft_printf("%p\n", room[i]->neighbor->room);

	ft_clean(room);


/*
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
*/
}
