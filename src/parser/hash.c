/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:47:54 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/04 14:39:13 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lemin.h"
/*
int		ft_hash(char *str, int size)
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
*/
unsigned int		ft_hash(char *str, int size)
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


/*
 * OBJECTIF :
 *
 * -Gerer les collisions.
 *  -> Pour gerer les collisions, il me faut un tableau de structures
 *  1.Je recupere l'indice via fonction de hachage.
 *  2.Je verifie que rien n'est deja a cet indice.
 *  3.Si rien n'y est, je retourne l'indice initialement trouve.
 *  Si quelque chose est trouve, j'ajoute un maillon a la liste chainee
*/
