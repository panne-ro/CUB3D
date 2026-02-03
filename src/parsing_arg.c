/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:57 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/03 18:10:04 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int		parse_extension(char *str)
{
	int		i;
	int		j;
	char	tmp[7000];

	i = 0;
	j = 0;
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
		tmp[j] = '\0';
		if (ft_strncmp(tmp, ".cub", ft_strlen(tmp)) == 0)
			return (0);
	}
	return (1);
}