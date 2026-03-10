/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:24:38 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/10 13:40:57 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//sub fonction of checkcontentmaster 
//return all of rgb in array of t_map for the ceiling
//faut faire bellek ya pas les erreurs d'over-nombre pour l'instant 
//(F 0,250,300,54654,484,31,5156,4,51,48,4,3,84,5)
void	check_content_cc(char *tmp, t_map *map, int i, char *line_read)
{
	line_read = readAndCleanLine(line_read, map);
	while (line_read)
	{
		i = -1;
		while (line_read[++i])
		{
			if (line_read[i] == 'C')
			{
				i++;
				if (!line_read[i])
					return ;
				while (line_read[i] && line_read[i] == ' ')
					i++;
				map->boolean = true;
				rgb_dispatch_info_file(line_read, tmp, i, map);
				free(line_read);
				return ;
			}
		}
		free(line_read);
		line_read = readAndCleanLine(line_read, map);
	}
	free(line_read);
}

// a sub_functions for CheckContent_XXXX
//copy a string in file at line_read[i] to tmp and return it (to free)
char	*copy_content(char *line_read, char *tmp, int i)
{
	int		j;
	char	*result;

	j = 0;
	while (line_read[i])
	{
		tmp[j] = line_read[i];
		j++;
		i++;
	}
	tmp[j] = 0;
	result = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(result, tmp, j + 1);
	free(line_read);
	return (result);
}

// sub fonction for dispatch rgb (floor or ceiling) into t_map data
void	rgb_dispatch_info_file(char *line_read, char *tmp, int i, t_map *map)
{
	int	j;
	int	nbr;

	nbr = 0;
	while (line_read[i] && nbr < 3)
	{
		j = 0;
		while (line_read[i] && line_read[i] != ',')
		{
			tmp[j] = line_read[i];
			j++;
			i++;
		}
		tmp[j] = 0;
		if (map->boolean)
			map->ceilingColor[nbr] = ft_atoi(tmp);
		else
			map->floorColor[nbr] = ft_atoi(tmp);
		i++;
		nbr++;
	}
}
