/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:58:24 by jfleury           #+#    #+#             */
/*   Updated: 2019/05/03 15:06:33 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_upstream(t_bfs *bfs, int *flag, t_data data)
{
	while (bfs->tmp_n != NULL)
	{
		if (bfs->tmp_n->flow == -1
			&& ((t_room*)(bfs->tmp_n->room))->visited == 0)
		{
			*flag = 1;
			bfs->tmp_r2->next = bfs->tmp_n->room;
			bfs->tmp_r2 = bfs->tmp_r2->next;
			bfs->tmp_r2->visited = 1;
			bfs->tmp_r2->source = bfs->tmp_r;
			bfs->tmp_r2->next = NULL;
			//ft_printf("REMONTEE : tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_source = %s\n", bfs->tmp_r->name, bfs->tmp_r2->name, bfs->tmp_r2->source->name);
			if (bfs->tmp_r2 == data.end_room)
				break ;
		}
		bfs->tmp_n = bfs->tmp_n->next;
	}
}

static void	ft_downstream(t_bfs *bfs, int *flag, t_data data)
{
	while (bfs->tmp_n != NULL)
	{
		if (((t_room*)(bfs->tmp_n->room))->visited == 0
			&& bfs->tmp_n->flow != 1)
		{
			*flag = 0;
			bfs->tmp_r2->next = bfs->tmp_n->room;
			bfs->tmp_r2 = bfs->tmp_r2->next;
			bfs->tmp_r2->visited = 1;
			bfs->tmp_r2->source = bfs->tmp_r;
			bfs->tmp_r2->next = NULL;
			//ft_printf("tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_source = %s\n", bfs->tmp_r->name, bfs->tmp_r2->name, bfs->tmp_r2->source->name);
			if (bfs->tmp_r2 == data.end_room)
				break ;
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
		i++;
	}
	bfs->tmp_r = data.start_room;
	bfs->tmp_r->source = NULL;
	bfs->tmp_r2 = bfs->tmp_r;
	bfs->tmp_r2->visited = 1;
}

int			ft_bfs(t_room **room, t_data data, t_room ***shortest_path)
{
	t_bfs		bfs;
	int			flag;
	int			ret;

	flag = 0;
	ft_init_data_bfs(&bfs, data, room);
	while (bfs.tmp_r2 != data.end_room)
	{
		bfs.tmp_n = bfs.tmp_r->neighbor;
		if (bfs.tmp_r->flow == 1)
			ft_upstream(&bfs, &flag, data);
		else
			ft_downstream(&bfs, &flag, data);
		//ft_printf("tmp_r = %s /\\ tmp_r2 = %s\n", bfs.tmp_r->name, bfs.tmp_r2->name);
		bfs.tmp_r = bfs.tmp_r->next;
		if (bfs.tmp_r == NULL)
			return (0);
	}
	if (!(ret = ft_create_shortest_path(&bfs, shortest_path)))
		return (-1);
	else
		return (1);
}
