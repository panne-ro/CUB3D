/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:24:38 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/30 16:24:09 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//sub fonction of check_content_master
//return all of rgb in array of t_map for the ceiling
//faut faire bellek ya pas les erreurs d'over-nombre pour l'instant
//(F 0,250,300,54654,484,31,5156,4,51,48,4,3,84,5)
void	check_content_cc(char *tmp, t_map *map, int i, char *line_read)
{
	i = -1;
	if (sub_check_content_cc(tmp, map, i, line_read))
		return ;
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
	return (result);
}

void	dispatch_color_at_good_place(t_map *map, char *tmp, int nbr)
{
	if (map->is_cc)
		map->ceilling_color[nbr] = ft_atoi(tmp);
	else if (map->is_fc)
		map->floor_color[nbr] = ft_atoi(tmp);
}

// sub fonction for dispatch rgb (floor or ceiling) into t_map data
int	rgb_dispatch_info_file(char *line_read, char *tmp, int i, t_map *map)
{
	int	j;
	int	nbr;

	nbr = 0;
	while (line_read[i])
	{
		j = 0;
		while (line_read[i] && line_read[i] != ',')
		{
			tmp[j] = line_read[i];
			if (!ft_isdigit(tmp[j]))
				return (-2);
			j++;
			i++;
		}
		tmp[j] = 0;
		dispatch_color_at_good_place(map, tmp, nbr);
		i++;
		nbr++;
		if (nbr > 3 || j > 3)
			return (-2);
	}
	return (0);
}

void	flush_and_reopen(t_map *map)
{
	flush_gnl(map->fd_map);
	close(map->fd_map);
	map->fd_map = open(map->file_path, O_RDONLY);
	map->reading_head = 0;
}
