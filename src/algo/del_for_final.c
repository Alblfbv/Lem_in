/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_for_final.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:28:29 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/25 19:31:48 by allefebv         ###   ########.fr       */
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
			ft_printf("\nPath n*%d :", j + 1);
			while (all_path[i][j]->path[k] != 0)
			{
				ft_printf(" %s -", all_path[i][j]->path[k]->name);
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
