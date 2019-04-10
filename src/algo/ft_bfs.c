/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:58:24 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/10 18:00:50 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room	**ft_bfs(t_room **room, t_lem lem)
{
	t_room		**shortest_path;
	t_room		*tmp_r;
	t_room		*tmp_r2;
	t_neighbor	*tmp_n;
	int			i;

	i = 0;
	while (i < lem.nb_room)
	{
		room[i]->visited = 0;
		i++;
	}
	tmp_r = lem.start_room;
	tmp_r->source = NULL;
	tmp_r2 = tmp_r;
	tmp_r2->visited = 1;
	//On continue tant qu'on a pas atteint la salle de fin
	while (tmp_r2 != lem.end_room)
	{
		//on se positionne sur le premier voisin de tmp_r, qui au debut est
		//le START du graphe
		tmp_n = tmp_r->neighbor;
		while (tmp_n != NULL
				&& (((t_room*)tmp_n->room)->visited == 1 || tmp_n->flow == 1))
		{
			//ft_printf("flow = %d\n", tmp_n->flow);
			tmp_n = tmp_n->next;
		}
		//tant qu'il reste un ou plusieurs voisin et que le voisin n'a pas ete visite alors :
		while (tmp_n != NULL)
		{
			if(((t_room*)(tmp_n->room))->visited == 0 && tmp_n->flow == 0)
			{
				//On chaine le voisin avec le maillon d'avant (sa source ou un voisin de la source)
				tmp_r2->next = tmp_n->room;
				//On avance sur le voisin qu'on vient d'ajouter
				tmp_r2 = tmp_r2->next;
				//On indique que le voisin a ete visite
				tmp_r2->visited = 1;
				//On indique sa source (de quel maillon il etait le voisin pour bfs)
				tmp_r2->source = tmp_r;
				//Si on a ajoute la END ROOM a la chaine, on s'arrete
				printf("tmp_r = %s /\\ tmp_r2 = %s /\\ tmp_r2_source = %s\n", tmp_r->name, tmp_r2->name, tmp_r2->source->name);
				//On met le next a NULL
				tmp_r2->next = NULL;
			}
			//On avance d'un voisin
			tmp_n = tmp_n->next;
		}
		//On a explore tous les voisin de TMP_R, on avance donc a son NEXT
		//Son NEXT n'est autre que son premier voisin, et on repete le processus
		tmp_r = tmp_r->next;
		if (tmp_r == NULL)
			return (NULL);
		printf("tmp_r = %s /\\ tmp_r2 = %s\n", tmp_r->name, tmp_r2->name);
	}
	tmp_r = tmp_r2;
	i = 1;
	//On remonte TMP_R2 (Qui normalement est a END) vers la source et on compte
	while (tmp_r2->source != NULL)
	{
		tmp_r2 = tmp_r2->source;
		i++;
	}
	//Malloc le tableau de la taille du chemin
	shortest_path = (t_room**)malloc(sizeof(t_room*) * (i + 1));
	shortest_path[i] = 0;
	i--;
	//On remet tmp_r2 a la fin
	tmp_r2 = tmp_r;
	//Boucle pour ajouter les adresses des rooms du chemin au tableau
	while (i >= 0)
	{
		shortest_path[i] = tmp_r2;
		tmp_r2 = tmp_r2->source;
		i--;
	}
	return (shortest_path);
}

/*
 *
 * Doit retourner un tableau contenant les addresses des rooms du plus court
 * chemin.
 *
 * Faire une file qui va stocker tous les voisins non visites de start
 * puis tous les voisins non visites des voisins de premier degre
 * puis tous les voisins non visites des voisins de deuxieme degre
 * Besoin de stocker sur chaque element de la file qui l'a ammene dans la file
 * Comme ca on pourra remonter la liste
 * Liste chainee
 */
