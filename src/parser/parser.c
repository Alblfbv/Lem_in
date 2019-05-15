/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/05/15 20:36:31 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_parser_return(char *line, t_data *data, int flag)
{
	ft_strdel(&line);
	if (data->nb_ants == 0 || !data->start_room || !data->end_room)
		return (ft_error());
	if (flag == 2)
		return (ft_malloc_error());
	return (1);
}

static void		ft_modif(int *flag, int *check, int f, int c)
{
	*flag = f;
	*check = c;
}

int				parser(t_data *data, t_room **room, int flag, int check)
{
	char	*line;

	ft_modif(&flag, &check, 0, 1);
	while ((get_next_line(0, &line)) == 1 && check == 1)
	{
		check = 0;
		if (!flag && ft_ants(line, data, &flag))
			check = 1;
		else if (flag && flag != 2 && ft_room(line, room, data, flag))
		{
			ft_modif(&flag, &check, 1, 1);
			data->nb_room++;
		}
		else if ((flag) && (ft_comment(line) || ft_command(line, &flag)))
			check = 1;
		else if ((flag == 1 || flag == 2) && ft_path(line, room))
			ft_modif(&flag, &check, 2, 1);
		if (check == 1)
			if (!(ft_lstadd_end(data->instructions,
				ft_lstnew(line, sizeof(char) * ((ft_strlen(line) + 1))))))
				return (ft_parser_return(line, data, 2));
		ft_strdel(&line);
	}
	return (ft_parser_return(line, data, 1));
}
