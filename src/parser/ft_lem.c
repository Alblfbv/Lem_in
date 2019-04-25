/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:13:34 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/25 17:08:19 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ft_check_int(char *s)
{
	int			i;
	long long	nb;

	i = 0;
	if (s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (0);
	nb = 0;
	while (ft_isdigit(s[i]))
	{
		if (nb * 10 + s[i] - 48 > 2147483647)
			return (0);
		nb = nb * 10 + s[i] - 48;
		i++;
	}
	if (s[i] != '\0')
		return (0);
	return (1);
}

int			ft_lem(char *line, t_data *data, int *flag)
{
	if (line[0] == '-')
		return (0);
	if (!ft_check_int(line))
		return (0);
	data->nb_lem = ft_atoi(line);
	*flag = 1;
	return (1);
}
