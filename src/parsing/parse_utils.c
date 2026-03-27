/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:55:37 by vboxuser          #+#    #+#             */
/*   Updated: 2026/03/27 15:39:57 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	flush_gnl(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
}

bool	check_color_format(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j > 2)
		return (true);
	return (false);
}

int	sub_ext_is_all_wall(t_map *map, int y, int x)
{
	while (map->mapChar[y])
	{
		x = 0;
		if (map->mapChar[y][0] == '0')
			return (0);
		while (map->mapChar[y][x])
		{
			if (map->mapChar[y][x] == '0')
			{
				if (!map->mapChar[y][x + 1] || !map->mapChar[y][x - 1]
				 || !map->mapChar[y - 1][x]
					|| !map->mapChar[y + 1][x])
					return (0);
				if (map->mapChar[y][x + 1] == ' ' || map->mapChar[y][x - 1]
					== ' ' || map->mapChar[y - 1][x] == ' '
					|| map->mapChar[y + 1][x] == ' ')
					return (0);
			}
			x++;
		}
		if (map->mapChar[y][ft_strlen(map->mapChar[y]) - 1] == '0')
			return (0);
		y++;
	}
	return (1);
}

bool	check_double(char first, char second, t_map *map)
{
	char	*line_read;
	int		i;
	int		j;

	i = 0;
	j = 0;
	flush_and_reopen(map);
	line_read = read_and_clean_line(NULL, map);
	while (line_read)
	{
		i = 0;
		while (line_read[i])
		{
			if (line_read[i] == first && line_read[i + 1]
				&& line_read[i + 1] == second)
				j++;
			i++;
		}
		free(line_read);
		line_read = read_and_clean_line(NULL, map);
	}
	if (j > 1)
		return (true);
	return (false);
}

bool	check_double_master(t_map *map)
{
	if (check_double('N', 'O', map))
		return (true);
	if (check_double('S', 'O', map))
		return (true);
	if (check_double('W', 'E', map))
		return (true);
	if (check_double('E', 'A', map))
		return (true);
	if (check_double('F', ' ', map))
		return (true);
	if (check_double('C', ' ', map))
		return (true);
	flush_gnl(map->fdMap);
	close(map->fdMap);
	map->fdMap = open(map->filePath, O_RDONLY);
	map->readingHead = 0;
	map->startMapInReading = 0;
	return (false);
}
