/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:10:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/01 17:54:46 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	return (0);
}

int		ft_check_room(char *line)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split(line, ' ');
	while (str[i] != 0)
		i++;
	if (i < 3)
		return (ft_free_str(str));
	if (ft_isdigit(str[i - 1]) == 0 || ft_isdigit(str[i - 2] == 0))
		return (ft_free_str(str));
	ft_free_str(str);
	return (1);
}
