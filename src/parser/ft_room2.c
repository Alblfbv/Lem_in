/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:12:38 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/25 17:39:19 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			ft_store_type2(char **str, t_room **room, t_data *data,
								t_room *tmp)
{
	if (ft_strequ(tmp->name, str[0]))
		data->start_room = tmp;
	else
	{
		while (!ft_strequ(tmp->name, str[0]))
		{
			if (ft_strequ(tmp->name, str[0]))
				data->start_room = tmp;
			tmp = tmp->next;
		}
	}
}

void			ft_store_type(char **str, t_room **room, t_data *data, int flag)
{
	int			key;
	t_room		*tmp;

	key = ft_hash(str[0], HASH_TAB);
	tmp = room[key];
	if (flag == 3)
		ft_store_type2(str, room, data, tmp);
	else if (flag == 4)
	{
		if (ft_strequ(tmp->name, str[0]))
			data->end_room = tmp;
		else
		{
			while (!ft_strequ(tmp->name, str[0]))
			{
				if (ft_strequ(tmp->name, str[0]))
					data->end_room = tmp;
				tmp = tmp->next;
			}
		}
	}
}

static int		ft_store_room2(char **str, t_room **room, int key)
{
	if (!(room[key] = (t_room*)malloc(sizeof(t_room))))
		return (0);
	room[key]->neighbor = NULL;
	room[key]->next = NULL;
	room[key]->name = str[0];
	room[key]->x = str[1];
	room[key]->y = str[2];
	room[key]->flow = 0;
	return (1);
}

static int		ft_store_room3(char **str, t_room *tmp, int key)
{
	if (ft_strequ(tmp->name, str[0])
		|| !(tmp->next = (t_room*)malloc(sizeof(t_room))))
		return (0);
	tmp->next->neighbor = NULL;
	tmp->next->next = NULL;
	tmp->next->name = str[0];
	tmp->next->x = str[1];
	tmp->next->y = str[2];
	tmp->next->flow = 0;
	return (1);
}

int				ft_store_room(char **str, t_room **room)
{
	int			key;
	t_room		*tmp;

	key = ft_hash(str[0], HASH_TAB);
	if (room[key] == NULL)
	{
		if (!(ft_store_room2(str, room, key)))
			return (0);
	}
	else
	{
		tmp = room[key];
		while (tmp->next != NULL)
		{
			if (ft_strequ(tmp->name, str[0]))
				return (0);
			tmp = tmp->next;
		}
		if (!(ft_store_room3(str, tmp, key)))
			return (0);
	}
	return (1);
}