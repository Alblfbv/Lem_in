/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:32:11 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/29 19:04:11 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_clean(t_room **room, t_data *data)
{
	int			i;
	t_neighbor	*tmp_n;
	t_neighbor	*tmp_n_nxt;
	t_room		*tmp_r;
	t_room		*tmp_r_nxt;

	i = 0;
	free(data->instructions);
	while (i < HASH_TAB)
	{
		if (room[i] != NULL)
		{
			tmp_r = room[i];
			while (tmp_r != NULL)
			{
				tmp_n = tmp_r->neighbor;
				while (tmp_n != NULL)
				{
					tmp_n_nxt = tmp_n->next;
					free(tmp_n);
					tmp_n = tmp_n_nxt;
				}
				free(tmp_r->name);
				tmp_r_nxt = tmp_r->next;
				free(tmp_r);
				tmp_r = tmp_r_nxt;
			}
		}
		i++;
	}
	free(room);
	return (0);
}

static int		ft_clean_refacto(t_room **room, t_data data)
{
	int			i;
	t_neighbor	*tmp_n;
	t_neighbor	*tmp_n_nxt;

	i = 0;
	while (i < data.nb_room)
	{
		tmp_n = room[i]->neighbor;
		while (tmp_n != NULL)
		{
			tmp_n_nxt = tmp_n->next;
			free(tmp_n);
			tmp_n = tmp_n_nxt;
		}
		free(room[i]->name);
		free(room[i]->x);
		free(room[i]->y);
		free(room[i]);
		i++;
	}
	free(room);
	return (0);
}

static int		ft_init_room(t_room ***room)
{
	int		i;

	i = 0;
	if (!(*room = (t_room**)malloc(sizeof(t_room*) * HASH_TAB)))
		return (0);
	while (i < HASH_TAB)
	{
		room[0][i] = NULL;
		i++;
	}
	return (1);
}

static int		ft_init_data(t_data *data, int argc, char **argv)
{
	if (argc > 2)
		return (0);
	if (argc == 2)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'c' && argv[1][2] == '\0')
			data->flag_print = 1;
		else
		{
			ft_printf("Error\n");
			return (0);
		}
	}
	if (argc == 1)
		data->flag_print = 0;
	data->nb_room = 0;
	data->nb_lem = 0;
	data->start_room = NULL;
	data->end_room = NULL;
	data->instructions = (t_list**)malloc(sizeof(t_list*));
	*data->instructions = NULL;
	return (1);
}

int				main(int argc, char **argv)
{
	t_data	data;
	t_room	**room;
	t_room	**final_room;
	int		i;

	i = 0;
	room = NULL;
	final_room = NULL;
	if (!(ft_init_data(&data, argc, argv)))
		return (0);
	if (!(ft_init_room(&room)))
		return (0);
	if (!(parser(&data, room)))
		return (ft_clean(room, &data));
	//ft_print_all(room, data);
	if (!(ft_refactoring_room(room, data, &final_room)))
		return (ft_clean(room, &data));
	if(!ft_algo(final_room, data))
		ft_printf("Error\n");
	ft_lstdel(data.instructions, &ft_free_ptr);
	free(data.instructions);
	ft_clean_refacto(final_room, data);
	free(room);
}
