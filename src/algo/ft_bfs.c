/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:58:24 by jfleury           #+#    #+#             */
/*   Updated: 2019/05/13 20:43:42 by allefebv         ###   ########.fr       */
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

static int	ft_check_circle(t_room *tmp_r, t_room *tmp_n)
{
	while (tmp_r->source != NULL)
	{
		if (tmp_r == tmp_n)
			return (1);
		tmp_r = tmp_r->source;
	}
	return (0);
}

static void	ft_init_data_bfs(t_bfs *bfs, t_data data, t_room **room)
{
	int	i;

	i = 0;
	while (i < data.nb_room)
	{
		room[i]->visited = 0;
		room[i]->upstream = 0;
		i++;
	}
	bfs->tmp_r = data.start_room;
	bfs->tmp_r->source = NULL;
	bfs->tmp_r2 = bfs->tmp_r;
	bfs->tmp_r2->visited = 1;
}

int			ft_create_shortest_path(t_bfs *bfs, t_room ***shortest_path)
{
	int			i;

	bfs->tmp_r = bfs->tmp_r2;
	i = 1;
	while (bfs->tmp_r2->source != NULL)
	{
		//ft_printf("tmp_r2 = %s / source = %s\n", bfs->tmp_r2->name, bfs->tmp_r2->source->name);
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
				bfs->tmp_r2->weight = bfs->tmp_r->weight - 1;
				bfs->tmp_r2->visited = 1;
				bfs->tmp_r2->upstream = 1;
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
				//ft_printf("tmp_up_n = %p /\\ tmp_up_r = %p\n", tmp_up_n->name, tmp_up_r->name);
				while (((tmp_up_n != data.start_room && tmp_up_n->source != data.start_room
						&& ((tmp_up_r->weight <= tmp_up_n->weight && tmp_up_n->flow == 1 && tmp_up_n->upstream == 0)
						|| (tmp_up_r->weight < tmp_up_n->weight && tmp_up_n->flow == 0))
						&& !ft_check_circle(tmp_up_r, tmp_up_n))))
				{
					tmp_up_source = tmp_up_n->source;
					tmp_up_n->source = tmp_up_r;
					if (tmp_up_n->flow == 1)
						tmp_up_n->weight = tmp_up_r->weight - 1;
					else
						tmp_up_n->weight = tmp_up_r->weight + 1;
					//ft_printf("up - s_n_initial = %s n = %s r = %s w_n = %d new_n_source %s\n", tmp_up_source->name, tmp_up_n->name, tmp_up_r->name, tmp_up_n->weight, tmp_up_n->source->name);
					tmp_up_r = tmp_up_n;
					tmp_up_n = tmp_up_source;
					ft_printf("tmp_up_n = %p /\\ tmp_up_r = %p\n", tmp_up_n, tmp_up_r);
				}
			}
		}
		bfs->tmp_n = bfs->tmp_n->next;
	}
}

static void	ft_downstream(t_bfs *bfs, t_data data)
{
	t_room	*tmp_up_n;
	t_room	*tmp_up_r;
	t_room	*tmp_up_source;

	while (bfs->tmp_n != NULL)
	{
		if (bfs->tmp_n->flow != 1)
		{
			//ft_printf("tmp_r = %s\n", bfs->tmp_r->name);
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
			else if (bfs->tmp_r->weight <= ((t_room*)(bfs->tmp_n->room))->weight
				&& ((t_room*)(bfs->tmp_n->room))->source != bfs->tmp_r)
			{
			//ft_printf("------>>>>> tmp_r = %s\n", bfs->tmp_r->name);
				tmp_up_n = (t_room*)bfs->tmp_n->room;
				tmp_up_r = bfs->tmp_r;
				//while (((tmp_up_r->weight <= tmp_up_n->weight && tmp_up_n->flow == 1 && tmp_up_n->upstream == 0)
				//		|| (tmp_up_r->weight < tmp_up_n->weight && tmp_up_n->flow == 0))
				while ((((tmp_up_n != data.start_room && tmp_up_n->source != data.start_room
						&& tmp_up_r->weight < tmp_up_n->weight && tmp_up_n->flow == 0))
						&& !ft_check_circle(tmp_up_r, tmp_up_n)))
				{
					tmp_up_source = tmp_up_n->source;
					tmp_up_n->source = tmp_up_r;
					if (tmp_up_n->flow == 1)
						tmp_up_n->weight = tmp_up_r->weight - 1;
					else
						tmp_up_n->weight = tmp_up_r->weight + 1;
					//ft_printf("down - source voisin = %s voisin = %s position actuelle = %s poids voisin = %d nouvelle source voisin %s\n", tmp_up_source->name, tmp_up_n->name, tmp_up_r->name, tmp_up_n->weight, tmp_up_n->source->name);
					tmp_up_r = tmp_up_n;
					tmp_up_n = tmp_up_source;
				}
			}
		}
		bfs->tmp_n = bfs->tmp_n->next;
	}
}


int			ft_bfs(t_room **room, t_data data, t_room ***shortest_path)
{
	t_bfs		bfs;
	int			ret;

	ft_init_data_bfs(&bfs, data, room);
	while (bfs.tmp_r2 != data.end_room)
	{
		bfs.tmp_n = bfs.tmp_r->neighbor;
		if (bfs.tmp_r->flow == 1)
			ft_upstream(&bfs, data);
		bfs.tmp_n = bfs.tmp_r->neighbor;
		//ft_printf("tmp_r %s upstream = %d\n", bfs.tmp_r->name, bfs.tmp_r->upstream);
		if (bfs.tmp_r->flow == 0 || bfs.tmp_r->upstream == 1)
			ft_downstream(&bfs, data);
		bfs.tmp_r = bfs.tmp_r->next;
		if (bfs.tmp_r == NULL)
			return (0);
	}
	if (bfs.tmp_r2 == data.end_room
		&& !(ret = ft_create_shortest_path(&bfs, shortest_path)))
		return (-1);
	else
		return (1);
}
