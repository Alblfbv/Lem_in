/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:36:04 by allefebv          #+#    #+#             */
/*   Updated: 2019/04/03 15:01:35 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	ft_clean(char **couple)
{
	while(couple[i] != 0)
	{
		free(couple[i]);
		i++;
	}
	free(couple);
}

static int	ft_path_error(char **couple)
{
	int	j;
	int	i;
	
	j = 0;
	i = 0;
	// On verifie qu'il y a bien deux parties separees par un tiret
	if (i != 2)
		return (0);
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
	return (1);
}

static int	ft_fill_neig(char **couple, t_room *tmp_r, t_neighbor *tmp_n, int i)
{
	if (tmp_n->name == NULL)
	{
		if (i == 0)
			tmp_n->room = tmp_r;
		else
			tmp_n->room = tmp_r;
		tmp_n->next = NULL;
	}
	else
	{
		while (tmp_n->next != NULL)
			tmp_n = tmp_n->next;
		if(!(tmp_n->next = (t_neighbor*)malloc(sizeof(t_neighbor))))
			return (0);
		tmp_n = tmp_n->next;
		if (i == 0)
			tmp_n->room = tmp_r;
		else
			tmp_n->room = tmp_r;
		tmp_n->next = NULL;
	}
	return (1);
}

static int	ft_path_check_room(char **couple, t_room **room)
{
	int			i;
	int			key;
	t_room		*tmp_r;
	t_neighbor	*tmp_n;

	i = 0;
	while (couple[i] != 0)
	{
		// On calcule la cle de hash pour chaque salle
		key = ft_hash(couple[i]);
		// Pointeur TMP pour avancer dans les salles sur le meme indice donne
		// par la fonction de hash au cas ou collisions lors du stockage fait
		// precedemment
		tmp_r = room[key];
		while (tmp_r != NULL && !ft_strequ(tmp_r->name, couple[i]))
			tmp_r->next = next;
		// Si tmp == NULL, cela veut dire qu'on a pas trouve la salle
		if (tmp_r == NULL)
			return (0);
		// Si tmp pas NULL, on a trouve la salle donc on va stocker le voisin 2
		// dans salle 1 et voisin 1 dans salle 2
		else
		{
			tmp_n = tmp_r->neighbor;
			if(!(ft_fill_neig(couple, tmp_r, tmp_n, i)))
				return (0);
		}
		i++;
	}
	return (1);
}

int			ft_path(char *line, t_room **room)
{
	char		**couple;

	// On recupere les 2 salles
	couple = ft_strsplit(line, '-');
	if(!(ft_path_error(couple)))
	{
		ft_clean(couple);
		return (0);
	}
	// Si ok, on applique le process aux deux salles
	if(!(ft_path_check_room(couple, room)))
		return (0);
	return (1);
}

/*
OBJECTIF :
-Verifier si les rooms existent
-Verifier si cette connexion n'existe pas deja
-Stocker dans ROOM 1 le voisin ROOM 2
-Stoker dans ROOM 2 le voisin ROOM 1
*/
