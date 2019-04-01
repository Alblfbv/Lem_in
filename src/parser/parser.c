/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfleury <jfleury@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:32 by jfleury           #+#    #+#             */
/*   Updated: 2019/04/01 15:04:53 by jfleury          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	**parser(t_struct **struct)
{
	char	**raw_data;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (GNL == 1)
	{
		if ((flag = ft_check_error(line)) == 0)
			return (ft_error(raw_data));
		raw_data = ft_add_line(line);
		i++;
	}
	ft_init_struct(struct); // prime(i * 3) et malloc de la taille et init a NULL
	ft_struct_store(line, struct);
	return (raw_data);
}
