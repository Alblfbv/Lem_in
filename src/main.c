/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:32:11 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/04 14:12:31 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

							//A SUPPRIMER POUR LE RENDU
static void	ft_print_all(t_room **room, t_lem *lem)
{
	int			i;
	t_neighbor	*tmp_n;
	t_room		*tmp_r;

	i = 0;
	while (i < HASH_TAB)
	{
		if (room[i] != NULL)
		{
			tmp_r = room[i];
			while (tmp_r != NULL)
			{
				tmp_n = tmp_r->neighbor;
				ft_printf("ROOM = %s\n", tmp_r->name);
				ft_printf("TYPE = %c\n", tmp_r->room_type);
				ft_printf("Neighbors of room = ");
				while (tmp_n != NULL)
				{
					ft_printf("%s ", ((t_room*)(tmp_n->room))->name);
					tmp_n = tmp_n->next;
				}
				tmp_r = tmp_r->next;
				ft_printf("\n\n");
			}
		}
		i++;
	}
	ft_printf("Start = %s\n", lem->name_start);
	ft_printf("End = %s\n", lem->name_end);
}

static int	ft_clean(t_room **room, t_lem *lem)
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
	free(lem->name_start);
	free(lem->name_end);
	return (0);
}

int		main(void)
{
	t_lem	lem;
	t_room	**room;
	int		i;

	i = 0;
	room = (t_room**)malloc(sizeof(t_room*) * HASH_TAB);
	while (i < HASH_TAB)
	{
		room[i] = NULL;
		i++;
	}
	parser(&lem, room);
	ft_print_all(room, &lem);
	ft_clean(room, &lem);
}
