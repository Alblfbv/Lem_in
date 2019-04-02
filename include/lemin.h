/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:34:08 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/02 12:54:47 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "../libft/include/libft.h"

typedef struct		s_lem
{
	int		nb_lem;

}					t_lem;


int		ft_hash(char *str, int size);
void	parser(t_lem *lem);
int		ft_check_lem(char *line);
void	ft_store_lem(t_lem *lem, char *line);
int		ft_check_comment(char *line);
int		ft_check_command(char *line);

#endif
