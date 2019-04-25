/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:10:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/25 17:39:20 by jfleury          ###   ########.fr       */
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
	if (str[i][0] == 'L')
		return (0);
	while (str[i] != 0)
		i++;
	if (i != 3)
		return (0);
	i--;
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
