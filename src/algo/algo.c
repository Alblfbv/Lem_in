/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:34:16 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/09 18:45:26 by allefebv         ###   ########.fr       */
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

int		ft_path_len(t_room *room)
{
	t_room		*tmp_r;
	t_neighbor	*tmp_n;
	int			len;

	tmp_r = room;
	len = 0;
	while (tmp_r != lem->name_end)
	{
		tmp_n = tmp_r->neighbor;
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		len++;
		tmp_r = tmp_n->room;
	}
	return (len);
}

t_room	**ft_fill_path(t_room **all_path, t_room *first, int len)
{
	int			i;
	t_room		*tmp_r;
	t_neighbor	*tmp_n;

	i = 0;
	all_path = (t_room**)malloc(sizeof(t_room*) * len);
	
	tmp_r = first;
	i = 0;
	while (tmp_r != lem->name_end)
	{
		tmp_n = tmp_r->neighbor;
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		all_path[i] = tmp_n->room;
		tmp_r = tmp_n->room;
	}
	return (all_path);
}

t_room	****ft_store_path(t_room **room, t_room ****all_path, t_lem *lem)
{
	t_room		*tmp_r;
	t_neighbor	*tmp_n;
	int			key;
	int			nb_path;
	int			i;
	int			j;

	tmp_r = START;
	tmp_n = tmp_r->neighbor;
	nb_path = 0;
	i = 0;
	while (tmp_n->next != NULL)
	{
		if (tmp_n->flow == 1)
			nb_path++;
		tmp_n = tmp_n->next;
	}
	while (all_path[j] != NULL)
		j++;
	*all_path = (t_room***)malloc(sizeof(t_room**) * nb_path);
	tmp_n = tmp_r->neighbor;
	while (i < nb_path)
	{
		while (tmp_n->flow != 1)
			tmp_n = tmp_n->next;
		len = ft_path_len(tmp_n->room);
		all_path[j][i] = ft_fill_path(all_path[j][i], tmp_n->room, len);
		i++;
	}
	return (all_path);
}

void	ft_edmond_karp(t_room **shortest_path)
{
	t_neighbor	*n_forth;
	t_neighbor	*n_back;
	int			i;

	i = 0;
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

int		algo(t_room **room, t_lem *lem)
{
	int		i;
	t_room	*shortest_path;
	t_room	****all_path;

	i = 0;
	all_path = (t_room****)malloc(sizeof(t_room***) * lem->nb_path)
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
