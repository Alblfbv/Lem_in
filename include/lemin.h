/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:34:08 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/22 16:59:45 by allefebv         ###   ########.fr       */
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


typedef struct 			s_neighbor
{
	void				*room;
	int					flow;
	int					storage_flow;
	struct s_neighbor	*next;
}						t_neighbor;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					flow;
	int					visit;
	char				room_type;
	short				visited;
	t_neighbor			*neighbor;
	struct s_room		*source;
	struct s_room		*next;
}						t_room;

typedef struct			s_coord
{
	int					x;
	int					y;
	struct s_coord		*next;
}						t_coord;

typedef struct			s_data
{
	int					nb_lem;
	int					nb_path;
	int					nb_room;
	char				**result_read;
	char				*tmp;
	int					j;
	t_room				*start_room;
	t_room				*end_room;
}						t_data;

typedef	struct			s_path
{
	t_room				**path;
	int					length;
	int					lems;
	int					steps;
}						t_path;

typedef struct			s_lems
{
	int					name;
	t_path				*path;
	t_room				*room;
}						t_lems;


unsigned int		ft_hash(char *str, int size);

int			parser(t_data *data, t_room **room);
int			ft_lem(char *line, t_data *data, int *flag);
int			ft_comment(char *line);
int			ft_command(char *line, t_data *data, t_room **room, int flag);
int			ft_room(char *line, t_room **room, t_data *data, char type);
int			ft_check_coord(char *line, t_coord **coord_tab);
int			ft_path(char *line, t_room **room);
int			ft_refactoring_room(t_room **room, t_data data, t_room ***final_room);
int			ft_algo(t_room **room, t_data data);
t_room		**ft_bfs(t_room **room, t_data data);
void		ft_compute_nb_lem(t_path **tab, t_data data);
t_path**	ft_chose_best_path(t_path ***all_path, t_data data);
int			**ft_create_path_tab(t_room ****all_path);
t_path		***ft_store_path(t_path ***all_path, t_data data);
void		ft_lem_manage(t_path **path, t_data data);

//A SUPPRIMER POUR LE RENDU
void		ft_print_paths(t_path ***all_path, t_data data);

#endif
