/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:34:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/09 15:36:16 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_clean(char **str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

void	ft_edmond_karp(t_room *shortest_path)
{
	t_neighbor	*n_forth;
	t_neighbor	*n_back;

	while (shortest_path[i] != 0)
	{
		if (shortest_path[i + 1] != 0)
		{
			n_forth = shortest_path[i]->neighbor;
			while (n_forth->room != shortest_path[i + 1])
				n_forth = n_forth->next;
			n_forth->flow = 1;
		}
		if (i != 0)
		{
			n_back = shortest_path[i]->neighbor;
			while (n_back->room != shortest_path[i - 1])
				n_back = n_back->next;
			n_back->flow = -1;
		}
		i++;
	}
}

t_room	***ft_store_path(t_room **room, t_room ***all_path, t_lem *lem)
{
	t_room	*tmp;
	int		key;

	key = ft_hash(lem->name_start, HASH_TAB);
	tmp = room[key];
	return (all_path);
}

int		algo(t_room **room, t_lem *lem)
{
	int		i;
	t_room	*shortest_path;
	t_room	***all_path;

	i = 0;
	all_path = (t_room***)malloc(sizeof(t_room**) * lem->nb_path)
	while (i < lem->nb_path)
	{
		shortest_path = ft_bfs(room, lem);
		ft_edmond_karp(shortest_path);
		all_path = ft_store_path(room, all_path);
		i++;
		ft_clean(shortest_path);
	}
	return (1);
}
