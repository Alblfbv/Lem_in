/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:58:24 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/22 19:13:23 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	**ft_bfs(t_room **room, t_data data)
{
	t_room		**shortest_path;
	t_room		*tmp_r;
	t_room		*tmp_r2;
	t_neighbor	*tmp_n;
	int			i;
	int			flag;

	i = 0;
	while (i < data.nb_room)
	{
		room[i]->visited = 0;
		i++;
	}
	tmp_r = data.start_room;
	tmp_r->source = NULL;
	tmp_r2 = tmp_r;
	tmp_r2->visited = 1;
	flag = 0;
	while (tmp_r2 != data.end_room)
	{
		tmp_n = tmp_r->neighbor;
		if (tmp_r->flow == 1 && flag == 0)
		{
			while(tmp_n != NULL)
			{
				if (tmp_n->flow == -1 && ((t_room*)(tmp_n->room))->visited == 0)
				{
					flag = 1;
					tmp_r2->next = tmp_n->room;
					tmp_r2 = tmp_r2->next;
					tmp_r2->visited = 1;
					tmp_r2->source = tmp_r;
					tmp_r2->next = NULL;
					//ft_printf("REMONTEE : tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_source = %s\n", tmp_r->name, tmp_r2->name, tmp_r2->source->name);
				}
				tmp_n = tmp_n->next;
			}
			tmp_r = tmp_r->next;
			if (tmp_r == NULL)
				return (NULL);
		}
		else
		{
			while (tmp_n != NULL)
			{
				if(((t_room*)(tmp_n->room))->visited == 0 && tmp_n->flow != 1)
				{
					flag = 0;
					tmp_r2->next = tmp_n->room;
					tmp_r2 = tmp_r2->next;
					tmp_r2->visited = 1;
					tmp_r2->source = tmp_r;
					//ft_printf("tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_source = %s\n", tmp_r->name, tmp_r2->name, tmp_r2->source->name);
					tmp_r2->next = NULL;
				}
				tmp_n = tmp_n->next;
			}
			tmp_r = tmp_r->next;
			if (tmp_r == NULL)
				return (NULL);
			//ft_printf("tmp_r = %s /\\ tmp_r2 = %s\n", tmp_r->name, tmp_r2->name);
		}
	}
	tmp_r = tmp_r2;
	i = 1;
	while (tmp_r2->source != NULL)
	{
		tmp_r2 = tmp_r2->source;
		i++;
	}
	shortest_path = (t_room**)malloc(sizeof(t_room*) * (i + 1));
	shortest_path[i] = 0;
	i--;
	tmp_r2 = tmp_r;
	while (i >= 0)
	{
		shortest_path[i] = tmp_r2;
		tmp_r2 = tmp_r2->source;
		i--;
	}
	return (shortest_path);
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


