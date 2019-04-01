/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:47:54 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/01 17:54:35 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	result = result % size;
	return (result);
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
