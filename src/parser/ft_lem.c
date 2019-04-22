/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:13:34 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/22 15:38:51 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_lem(char *line, t_data *data, int *flag)
{
	int		i;

	i = 0;
	while (line[i] != 0)
	{
		if (ft_isdigit(line[i]) == 0)
			return (0);
		i++;
	}
	data->nb_lem = ft_atoi(line);
	*flag = 1;
	return (1);
}
