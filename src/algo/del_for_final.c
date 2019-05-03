/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_for_final.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:28:29 by allefebv          #+#    #+#             */
/*   Updated: 2019/05/03 14:34:36 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
ft_printf("REMONTEE : tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_source = %s\n", tmp_r->name, tmp_r2->name, tmp_r2->source->name);
ft_printf("tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_source = %s\n", tmp_r->name, tmp_r2->name, tmp_r2->source->name);
ft_printf("tmp_r = %s /\\ tmp_r2 = %s\n", tmp_r->name, tmp_r2->name);
*/

#include "lemin.h"

void	ft_print_paths(t_path ***all_path)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (all_path[i] != 0)
	{
		ft_printf("\nEdmonds-Karp n*%d :", i + 1);
		j = 0;
		while (all_path[i][j] != 0)
		{
			k = 0;
			ft_printf("\nPath n*%d ", j + 1);
			ft_printf("/\\ Len = %d\n", all_path[i][j]->length);
			while (all_path[i][j]->path[k] != 0)
			{
				ft_printf("%s - ", all_path[i][j]->path[k]->name);
				k++;
			}
			j++;
		}
		i++;
		ft_printf("\n\n");
	}
}

void	ft_print_bfs(t_room **shortest_path)
{
	int	i;

	i = 0;
	ft_printf("shortest path = ");
	while (shortest_path && shortest_path[i] != 0)
	{
		ft_printf(" %s -", shortest_path[i]->name);
		i++;
	}
	ft_printf("\n");
}

void		ft_print_all(t_room **room, t_data data)
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
				ft_printf("KEY = %d\n", ft_hash(tmp_r->name, HASH_TAB));
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
	if (data.start_room != NULL)
		ft_printf("Start = %s\n", data.start_room->name);
	if (data.end_room != NULL)
		ft_printf("End = %s\n", data.end_room->name);
}


