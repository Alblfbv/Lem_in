/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:58:24 by jfleury           #+#    #+#             */
/*   Updated: 2019/05/03 20:47:48 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//				ft_printf("tmp_r = %s /\\ tmp_n = %s /\\ SOURCE = %s\n", bfs->tmp_r->name, ((t_room*)(bfs->tmp_n->room))->name, ((t_room*)(bfs->tmp_n->room))->source->name);

#include "lemin.h"

void		ft_print_file(t_room *start)
{
	ft_printf("file from tmp_r  = ");
	while (start != NULL)
	{
		ft_printf("%s - ", start->name);
		start = start->next;
	}
	ft_printf("\n");
}

static void	ft_upstream(t_bfs *bfs, t_data data)
{
	t_room	*tmp_up_n;
	t_room	*tmp_up_r;
	t_room	*tmp_up_source;

	while (bfs->tmp_n != NULL)
	{
		//Recherche de voisin a remonter (flot -1) et non visite
		//Changer la non visite par les ponderations
		if (bfs->tmp_n->flow == -1)
		{
			if (((t_room*)(bfs->tmp_n->room))->visited == 0)
			{
				bfs->tmp_r2->next = (t_room*)bfs->tmp_n->room;
				bfs->tmp_r2 = bfs->tmp_r2->next;
				bfs->tmp_r2->visited_up = 1;
				bfs->tmp_r2->upstream = 1;
				bfs->tmp_r2->weight = bfs->tmp_r->weight - 1;
				bfs->tmp_r2->visited = 1;
				bfs->tmp_r2->source = bfs->tmp_r;
				bfs->tmp_r2->next = NULL;
				//ft_printf("REMONTEE : tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_flow = %d /\\ tmp_r2 weight = %d\n", bfs->tmp_r->name, bfs->tmp_r2->name, bfs->tmp_r2->flow, bfs->tmp_r2->weight);
				if (bfs->tmp_r2 == data.end_room)
					break ;
			}
			else if (bfs->tmp_r->weight <= ((t_room*)(bfs->tmp_n->room))->weight
					&& ((t_room*)(bfs->tmp_n->room))->source != bfs->tmp_r)
			{
				tmp_up_n = (t_room*)bfs->tmp_n->room;
				tmp_up_r = bfs->tmp_r;
				while (tmp_up_r->weight <= tmp_up_n->weight && tmp_up_n->source != data.start_room)
				{
					tmp_up_source = tmp_up_n->source;
					tmp_up_n->source = tmp_up_r;
					tmp_up_n->weight = bfs->tmp_r->weight - 1;
					//ft_printf("source = %s n = %s r = %s\n", tmp_up_source->name, tmp_up_n->name, tmp_up_r->name);
					tmp_up_r = tmp_up_n;
					tmp_up_n = tmp_up_source;
				}
			}
		}
		bfs->tmp_n = bfs->tmp_n->next;
	}
}

static void	ft_downstream(t_bfs *bfs, t_data data)
{
	while (bfs->tmp_n != NULL)
	{
		if (bfs->tmp_n->flow != 1)
		{
			if (((t_room*)(bfs->tmp_n->room))->visited == 0)
			{
				bfs->tmp_r2->next = (t_room*)bfs->tmp_n->room;
				bfs->tmp_r2 = bfs->tmp_r2->next;
				bfs->tmp_r2->visited = 1;
				bfs->tmp_r2->source = bfs->tmp_r;
				bfs->tmp_r2->weight = bfs->tmp_r2->source->weight + 1;
				bfs->tmp_r2->next = NULL;
				//ft_printf("tmp_r = %s /\\ tmp_r2 = %s /\\ flow_r2 = %d /\\ tmp_r2 weight = %d\n", bfs->tmp_r->name, bfs->tmp_r2->name, bfs->tmp_r2->flow, bfs->tmp_r2->weight);
				if (bfs->tmp_r2 == data.end_room)
					break ;
			}
		}
		else if (bfs->tmp_r->weight <= ((t_room*)(bfs->tmp_n->room))->weight
				&& ((t_room*)(bfs->tmp_n->room))->source != bfs->tmp_r)
		{
			((t_room*)(bfs->tmp_n->room))->source = bfs->tmp_r;
			((t_room*)(bfs->tmp_n->room))->weight = bfs->tmp_r->weight - 1;
		}
		bfs->tmp_n = bfs->tmp_n->next;
	}
}

int			ft_create_shortest_path(t_bfs *bfs, t_room ***shortest_path)
{
	int			i;

	bfs->tmp_r = bfs->tmp_r2;
	i = 1;
	while (bfs->tmp_r2->source != NULL)
	{
		bfs->tmp_r2 = bfs->tmp_r2->source;
		i++;
	}
	if (!(*shortest_path = (t_room**)malloc(sizeof(t_room*) * (i + 1))))
		return (ft_malloc_error());
	shortest_path[0][i] = 0;
	i--;
	bfs->tmp_r2 = bfs->tmp_r;
	while (i >= 0)
	{
		shortest_path[0][i] = bfs->tmp_r2;
		bfs->tmp_r2 = bfs->tmp_r2->source;
		i--;
	}
	return (1);
}

static void	ft_init_data_bfs(t_bfs *bfs, t_data data, t_room **room)
{
	int	i;

	i = 0;
	while (i < data.nb_room)
	{
		room[i]->visited = 0;
		room[i]->visited_up = 0;
		room[i]->upstream = 0;
		i++;
	}
	bfs->tmp_r = data.start_room;
	bfs->tmp_r->source = NULL;
	bfs->tmp_r2 = bfs->tmp_r;
	bfs->tmp_r2->visited = 1;
	bfs->tmp_r2->visited_up = 1;
}

int			ft_bfs(t_room **room, t_data data, t_room ***shortest_path)
{
	t_bfs		bfs;
	int			ret;

	ft_init_data_bfs(&bfs, data, room);
	while (bfs.tmp_r2 != data.end_room)
	{
		bfs.tmp_n = bfs.tmp_r->neighbor;
		//ft_print_file(bfs.tmp_r);
		if (bfs.tmp_r->flow == 1)
		{
			ft_upstream(&bfs, data);
		}
		if (bfs.tmp_r->flow == 0 || (bfs.tmp_r->flow == 1 && bfs.tmp_r->upstream == 1))
		{
			ft_downstream(&bfs, data);
		}
		bfs.tmp_r = bfs.tmp_r->next;
		if (bfs.tmp_r == NULL)
			return (0);
	}
	if (!(ret = ft_create_shortest_path(&bfs, shortest_path)))
		return (-1);
	else
		return (1);
}
