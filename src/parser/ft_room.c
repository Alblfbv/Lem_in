/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:10:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 17:45:52 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
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
*/
int		ft_room(char *line, t_room **room)
{
	char	**str;
//	int		i;
	int		key;
	t_room	*tmp;


	str = ft_strsplit(line, ' ');
	tmp = NULL;
// Fonction de verif
/*
	i = 0;

	while (str[i] != 0)
		i++;
	if (i != 3)
		return (ft_free_str(str));
	if (ft_isdigit(str[i - 1]) == 0 || ft_isdigit(str[i - 2] == 0))
		return (ft_free_str(str));
	ft_free_str(str);

// Fonction de stockage
*/
	key = ft_hash(str[0], HASH_TAB);
	if (*(room + key) == NULL)
	{
		room[key] = (t_room*)malloc(sizeof(t_room));
		room[key]->next = NULL;
		room[key]->name = str[0];
		ft_printf("A\n");
	}
	else
	{
		ft_printf("B\n");
		tmp = room[key];
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_room*)malloc(sizeof(t_room));
		ft_printf("%p\n", tmp);
		tmp = tmp->next;
		ft_printf("%p\n", tmp);
		tmp->next = NULL;
		tmp->name = str[0];
	}
	return (1);
}
