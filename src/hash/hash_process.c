/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allefebv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:34:07 by allefebv          #+#    #+#             */
/*   Updated: 2019/03/29 12:05:53 by allefebv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

typedef	struct	s_node
{
	char		*name;
}				t_node;

int		hash_function(char *key, int size)
{
	int	value;
	int	i;

	i = 0;
	while (key[i] != '\0')
	{
		value = value + key[i] * i;
		i++;
	}
	value = value % size;
	return (value);
}

t_node	*hash_table(int size, t_node *node_tab, char *key)
{
	int	value;
	value = hash_function(key, size);
	if ((node_tab + value)->name == NULL)
		(node_tab + value).name = strdup(key);
	node_tab[value]->name = strdup(key);
	return (node_tab);
}

int		main(int argc, char **argv)
{
	t_node	*node_tab;

	node_tab = (t_node*)malloc(sizeof(t_node) * 3000);
	hash_table(1000, node_tab, argv[1]);
	printf("%s", (node_tab + hash_function(argv[1], 1000))->name);
	return (0);
}
