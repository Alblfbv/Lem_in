/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:36:04 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/02 19:27:46 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_path(char *line, t_room **room)
{
	char	**couple;
	t_room	*tmp_r;
	t_neighbor	*tmp_n;
	int		i;
	int		j;

	// On recupere les 2 salles
	couple = ft_strsplit(line, '-');
	i = 0;
	// On verifie qu'il n'y a pas d'espace dans le nom de salle
	while (couple[i] != 0)
	{
		j = 0;
		while (couple[i][j] != '\0' && couple[i][j] != ' ')
			j++;
		if (couple[i][j] != '\0')
			return (0);
		i++;
	}
	// On verifie qu'il y a bien deux parties separees par un tiret
	if (i != 2)
		return (0);
	i = 0;
	// Si ok, on applique le process aux deux salles
	while (i < 2)
	{
		// On calcule la cle de hash pour chaque salle
		key = ft_hash(couple[i]);
		// Pointeur TMP pour avancer dans les salles sur le meme indice donne
		// par la fonction de hash au cas ou collisions lors du stockage avant
		tmp = room[key];
		while (tmp != NULL && !ft_strequ(tmp->name, couple[i]))
			tmp->next = next;
		// Si tmp == NULL, cela veut dire qu'on a pas trouve la salle
		if (tmp == NULL)
			return (0);
		// Si tmp pas NULL, on a trouve la salle donc on va stocker le voisin 2
		// dans salle 1 et voisin 1 dans salle 2
		else
		{
			tmp_n = tmp->neighbor;
			if (tmp_n->name == NULL)
			{
				tmp_n->name = ft_strdup(couple[i]);
				tmp_n->next = NULL;
			}
			else
			{
				while (tmp_n->next != NULL)
					tmp_n = tmp_n->next;
				tmp_n->next = (t_neighbor*)malloc(sizeof(t_neighbor));
				tmp_n = tmp_n->next;
				tmp_n->name = ft_strdup(couple[i]);
				tmp_n->next = NULL;
			}
		}
	}

}

OBJECTIF :
-Verifier si les rooms existent
-Verifier si cette connexion n'existe pas deja
-Stocker dans ROOM 1 le voisin ROOM 2
-Stoker dans ROOM 2 le voisin ROOM 1
