/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:13:34 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 15:16:50 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_lem(char *line)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if (ft_isdigit(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_store_lem(t_lem *lem, char *line)
{
	lem->nb_lem = ft_atoi(line);
}
