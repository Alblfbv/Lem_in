/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:10:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/25 17:01:18 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_clean(char **str, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		while (str[i] != 0)
		{
			free(str[i]);
			i++;
		}
	}
	free(str);
	return (0);
}

static int		ft_check_room(char **str)
{
	int		i;
	int		j;

	i = 0;
	if (str[0][0] == 'L')
		return (0);
	while (str[i] != 0)
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '-')
			return (0);
		i++;
	}
	i = 2;
	while (i != 0)
	{
		j = 0;
		while (str[i][j] != 0)
		{
			if (j == 0 && (str[i][j] == '+' || str[i][j] == '-'))
				j++;
			if (!(ft_isdigit(str[i][j])))
				return (0);
			j++;
		}
		i--;
	}
	return (1);
}

static void		ft_store_type(char **str, t_room **room, t_data *data, int flag)
{
	int			key;
	t_room		*tmp;

	key = ft_hash(str[0], HASH_TAB);
	tmp = room[key];
	if (flag == 3)
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
		room[key]->name = str[0];
		room[key]->x = str[1];
		room[key]->y = str[2];
		room[key]->flow = 0;
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
		if (ft_strequ(tmp->name, str[0])
			|| !(tmp->next = (t_room*)malloc(sizeof(t_room))))
			return (0);
		tmp->next->neighbor = NULL;
		tmp->next->next = NULL;
		tmp->next->name = str[0];
		tmp->next->x = str[1];
		tmp->next->y = str[2];
		tmp->next->flow = 0;
	}
	return (1);
}

int				ft_room(char *line, t_room **room, t_data *data, int flag)
{
	char		**str;
	int			key;

	str = ft_strsplit(line, ' ');
	key = ft_hash(str[0], HASH_TAB);
	if (!(ft_check_room(str)))
		return (ft_clean(str, 1));
	if (!(ft_store_room(str, room)))
		return (ft_clean(str, 1));
	ft_store_type(str, room, data, flag);
	ft_clean(str, 0);
	return (1);
}
