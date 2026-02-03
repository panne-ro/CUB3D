/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:57 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/03 17:39:47 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		parse_extension(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while(str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		while(str[i])
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		if (ft_strcmp())
	}
}