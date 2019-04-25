/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:47:54 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/25 14:41:36 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

unsigned int		ft_hash(char *str, int size)
{
	int		i;
	int		j;
	int		result;

	i = 0;
	result = 0;
	j = 1;
	while (str[i] != 0)
	{
		result = result + ((int)str[i] * j);
		i++;
		j = j + 2;
	}
	result = result * 1009;
	result = result % size;
	return (result);
}

/*
unsigned int	ft_hash(char *str, int size)
{
	int				i;
	unsigned int	hash;

	i = 0;
	hash = 0;
	while (str[i] != 0)
	{
		hash += str[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	hash = hash % size;
	return (hash);
}
*/
