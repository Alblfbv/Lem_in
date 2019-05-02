/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/05/02 17:39:13 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		ft_parser_return(char *line, t_data *data)
{
	ft_strdel(&line);
	if (data->nb_ants == 0)
		return (ft_error());
	return (1);
}

/*int			ft_init_coord_tab(t_coord ***coord_tab)
{
	int	i;

	i = 0;
	if (!(*coord_tab = (t_coord**)malloc(sizeof(t_coord*) * HASH_TAB)))
		return (0);
	while (i < HASH_TAB)
	{
		(*coord_tab)[i] = NULL;
		i++;
	}
	return (1);
}*/

static void		ft_modif(int *flag, int *check, int f, int c)
{
	*flag = f;
	*check = c;
}

int				parser(t_data *data, t_room **room)
{
	char	*line;
	int		flag;
	int		check;

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
			ft_lstadd_end(data->instructions,
				ft_lstnew(line, sizeof(char) * ((ft_strlen(line) + 1))));
		ft_strdel(&line);
	}
	return (ft_parser_return(line, data));
}
