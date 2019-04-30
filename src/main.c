/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 10:32:11 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/30 16:33:49 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
		return (ft_clean_main(room, &data));
	if (!(ft_refactoring_room(room, data, &final_room)))
		return (ft_clean_main(room, &data));
	if (!ft_algo(final_room, data))
		ft_printf("Error\n");
	ft_lstdel(data.instructions, &ft_free_ptr);
	free(data.instructions);
	ft_clean_refacto(final_room, data);
	free(room);
}
