/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:32:11 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/12 12:00:00 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

							//A SUPPRIMER POUR LE RENDU
static void	ft_print_all(t_room **room, t_lem lem)
{
	int			i;
	t_neighbor	*tmp_n;
	t_room		*tmp_r;

	i = 0;
	while (i < HASH_TAB)
	{
		if (room[i] != NULL)
		{
			ft_printf("Test\n");
			tmp_r = room[i];
			while (tmp_r != NULL)
			{
				tmp_n = tmp_r->neighbor;
				ft_printf("ROOM = %s\n", tmp_r->name);
				ft_printf("KEY = %d\n", ft_hash(tmp_r->name, HASH_TAB));
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
	ft_printf("Start = %s\n", lem.start_room->name);
	ft_printf("End = %s\n", lem.end_room->name);
}

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

static int	ft_clean_refacto(t_room **room, t_lem lem)
{
	int	i;

	i = 0;
	while (i < lem.nb_room)
	{
		free(room[i]);
		i++;
	}
	free(room);
	return (0);
}

static int		ft_init_room(t_room ***room)
{
	int		i;

	i = 0;
	if (!(*room = (t_room**)malloc(sizeof(t_room*) * HASH_TAB)))
		return (0);
	while (i < HASH_TAB)
	{
		room[0][i] = NULL;
		i++;
	}
	return (1);
}

static void		ft_print_result(t_lem *lem)
{
	int		i;

	i = 0;
	while (lem->result_read[i] != 0)
	{
		ft_printf("%s\n", lem->result_read[i]);
		i++;
	}
}

int		main(void)
{
	t_lem	lem;
	t_room	**room;
	t_room	**final_room;
	int		i;

	i = 0;
	room = NULL;
	final_room = NULL;
	if (!(ft_init_room(&room)))
		return (0);
	if (!(parser(&lem, room)))
		return (ft_clean(room));
	if (!(ft_refactoring_room(room, lem, &final_room)))
		return (ft_clean(room));
//	ft_print_all(room, lem);
//	ft_algo(final_room, lem);
	ft_print_result(&lem);
	ft_clean_refacto(room, lem);
}
