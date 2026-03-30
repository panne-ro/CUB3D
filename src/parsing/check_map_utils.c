/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 21:06:50 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/30 13:11:04 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// function for recall get_next_line into line_read and change the \n to \0
char	*read_and_clean_line(char *line_read, t_map *map)
{
	int	i;

	i = 0;
	line_read = get_next_line(map->fdMap);
	if (!line_read)
		return (line_read);
	map->readingHead++;
	while (line_read[i])
	{
		if (line_read[i] == '\n')
		{
			line_read[i] = 0;
			break ;
		}
		i++;
	}
	return (line_read);
}

bool	sub_loop_master_in_verif_map(t_map *map, int *i, int *j,
	int *nbr_player)
{
	bool	map_is_start;

	map_is_start = false;
	while (map->mapChar[*i])
	{
		*j = 0;
		if (ft_strlen(map->mapChar[*i]) == 0)
			return (true);
		map->isClosed = true;
		if (!map_is_start && ft_strlen(map->mapChar[*i]))
			map_is_start = true;
		if (map_is_start && ft_strlen(map->mapChar[*i]) == 1
			&& map->mapChar[*i][0] == '\n')
			return (true);
		if (sub_loop_verif_map(map, i, j, nbr_player) == true)
			return (true);
		*i = *i + 1;
	}

	return (false);
}

bool	sub_loop_verif_map(t_map *map, int *i, int *j, int *nbr_player)
{
	while (map->mapChar[*i][*j])
	{
		if ((map->mapChar[*i][*j] != '0' && map->mapChar[*i][*j] != '1')
			&& map->mapChar[*i][*j] != ' ' && (map->mapChar[*i][*j] != 'E'
			&& map->mapChar[*i][*j] != 'W' && map->mapChar[*i][*j] != 'N'
			&& map->mapChar[*i][*j] != 'S'))
			return (true);
		if (map->mapChar[*i][*j] == 'E' || map->mapChar[*i][*j] == 'W'
			|| map->mapChar[*i][*j] == 'N' || map->mapChar[*i][*j] == 'S')
		{
			map->player_x = *j;
			map->player_y = *i;
			map->start_dir = map->mapChar[*i][*j];
			*nbr_player = *nbr_player + 1;
		}
		*j = *j + 1;
	}
	return (false);
}

int	check_flood_fill(t_map *map, int x, int y)
{
	if (y < 0 || x < 0)
	{
		map->isClosed = false;
		return (1);
	}
	if (!map->copy_map[y])
	{
		map->isClosed = false;
		return (1);
	}
	if (x >= (int)ft_strlen(map->copy_map[y]))
	{
		map->isClosed = false;
		return (1);
	}
	if (map->copy_map[y][x] == ' ')
	{
		map->isClosed = false;
		return (1);
	}
	return (0);
}

void	flood_fill(int x, int y, t_map *map)
{
	if (check_flood_fill(map, x, y))
		return ;
	if (map->copy_map[y][x] == '1' || map->copy_map[y][x] == 'X')
		return ;
	map->copy_map[y][x] = 'X';
	flood_fill(x + 1, y, map);
	flood_fill(x - 1, y, map);
	flood_fill(x, y + 1, map);
	flood_fill(x, y - 1, map);
}
