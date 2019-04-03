/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:13:34 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/03 13:03:35 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_lem(char *line, t_lem *lem, int *flag)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if (ft_isdigit(line[i]) == 0)
			return (0);
		i++;
	}
	lem->nb_lem = ft_atoi(line);
	*flag = 1;
	return (1);
}
