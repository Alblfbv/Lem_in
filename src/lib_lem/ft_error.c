/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 17:12:21 by allefebv          #+#    #+#             */
/*   Updated: 2019/05/14 17:12:41 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_malloc_error(void)
{
	ft_printf("Memory Allocation Error\n");
	return (0);
}

int			ft_error(void)
{
	ft_printf("Error\n");
	return (0);
}
