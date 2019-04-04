/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:10:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/04 16:02:00 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_clean(char **str)
{
	int			i;

	i = 0;
	while (str[i] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int		ft_check_room(char **str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != 0)
		i++;
	ft_printf("i = %d\n", i);
	if (i != 3)
		return (0);
	i--;
	while (i != 0)
	{
		j = 0;
		while (str[i][j] != 0)
		{
			if (!(ft_isdigit(str[i][j])))
				return (0);
			j++;
		}
		i--;
	}
	return (1);
}

static void		ft_store_type(char **str, t_room **room, t_lem *lem, char type)
{
	int			key;

	key = ft_hash(str[0], HASH_TAB);
	if (type == 'S')
	{
		lem->name_start = ft_strdup(str[0]);
		room[key]->room_type = type;
	}
	if (type == 'E')
	{
		lem->name_end = ft_strdup(str[0]);
		room[key]->room_type = type;
	}
	if (type == 'M')
		room[key]->room_type = type;
}

static int		ft_store_room(char **str, t_room **room)
{
	int			key;
	t_room		*tmp;

	key = ft_hash(str[0], HASH_TAB);
	if (room[key] == NULL)
	{
		if (!(room[key] = (t_room*)malloc(sizeof(t_room))))
			return (0);
		room[key]->neighbor = NULL;
		room[key]->next = NULL;
		room[key]->name = ft_strdup(str[0]);
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
		if (ft_strequ(tmp->name, str[0]) != 0
			|| !(tmp->next = (t_room*)malloc(sizeof(t_room))))
			return (0);
		tmp->next->neighbor = NULL;
		tmp->next->next = NULL;
		tmp->next->name = ft_strdup(str[0]);
	}
	return (1);
}

int				ft_room(char *line, t_room **room, t_lem *lem, char type)
{
	char		**str;
	int			key;

	str = ft_strsplit(line, ' ');
	key = ft_hash(str[0], HASH_TAB);
	if (!(ft_check_room(str)))
		return (ft_clean(str));
	if (!(ft_store_room(str, room)))
		return (ft_clean(str));
	ft_store_type(str, room, lem, type);
	room[key]->x = ft_atoi(str[1]);
	room[key]->y = ft_atoi(str[2]);
	ft_clean(str);
	return (1);
}
