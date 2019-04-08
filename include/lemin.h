/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:34:08 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/04 16:43:38 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/include/libft.h"

# define HASH_TAB 20011

typedef struct			s_lem
{
	int					nb_lem;
	char				*name_start;
	char				*name_end;
}						t_lem;

typedef struct 			s_neighbor
{
	void				*room;
	struct s_neighbor	*next;
}						t_neighbor;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	char				room_type;
	t_neighbor			*neighbor;
	struct s_room		*next;
}						t_room;

typedef struct			s_coord
{
	int					x;
	int					y;
	struct s_coord		*next;
}						t_coord;

unsigned int		ft_hash(char *str, int size);

int		parser(t_lem *lem, t_room **room);
int		ft_lem(char *line, t_lem *lem, int *flag);
int		ft_comment(char *line);
int		ft_command(char *line, t_lem *lem, t_room **room, int flag);
int		ft_room(char *line, t_room **room, t_lem *lem, char type);
int		ft_check_coord(char *line, t_coord **coord_tab);
int		ft_path(char *line, t_room **room);

#endif
