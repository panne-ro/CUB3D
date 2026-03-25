/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:15:12 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/25 14:13:23 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//check map in map file return a bool for error like:
//true = error find
//false = map is ok
bool	check_map(t_map *map)
{
	int		i;
	int		test;
	char	*line_read;

	test = 0;
	line_read = NULL;
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
		i = 0;
		while (line_read[i] && map->startMapInReading == 0)
		{
			if (line_read[i] != ' ' && line_read[i] != '\n'
				&& line_read[i] != '\f' && line_read[i] != '\r'
				&& line_read[i] != '\t' && line_read[i] != '\n'
				&& line_read[i] != '\v')
				map->startMapInReading = map->readingHead;
			i++;
		}
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
	if (test > 1)
		return (true);
	return (false);
}

char	*put_reading_head_in_place(t_map *map)
{
	char	*line_read;

	line_read = NULL;
	map->LineOfEof = map->readingHead;
	flush_gnl(map->fdMap);
	close(map->fdMap);
	map->fdMap = open(map->filePath, O_RDONLY);
	map->readingHead = 0;
	line_read = read_and_clean_line(line_read, map);
	while (line_read && map->readingHead < map->startMapInReading)
	{
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
	return (line_read);
}

void	sub_parse_map(char *line_read, t_map *map, int i, int j)
{
	line_read = put_reading_head_in_place(map);
	map->mapChar = malloc(sizeof(char *)
			* (map->LineOfEof - map->startMapInReading + 2));
	map->heightOfMap = map->LineOfEof - map->startMapInReading + 1;
	while (line_read)
	{
		i = 0;
		while (line_read[i])
			i++;
		map->mapChar[j] = malloc(sizeof(char) * (i + 2));
		i = 0;
		while (line_read[i])
		{
			map->mapChar[j][i] = line_read[i];
			i++;
		}
		map->mapChar[j][i] = '\0';
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
		j++;
	}
	map->mapChar[j] = NULL;
	free(line_read);
}

int	ext_is_all_wall(t_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (map->mapChar[0][x])
	{
		if (map->mapChar[0][x] == '0')
			return (0);
		x++;
	}
	while (map->mapChar[y + 1])
		y++;
	x = 0;
	while (map->mapChar[y][x])
	{
		if (map->mapChar[y][x] == '0')
			return (0);
		x++;
	}
	if (sub_ext_is_all_wall(map, 0, 0) == 0)
		return (0);
	return (1);
}

// sub_function for parse map only in map file return in map->
void	parse_map(t_map *map)
{
	char	*line_read;

	line_read = NULL;
	if (check_map(map))
		return ;
	sub_parse_map(line_read, map, 0, 0);
}
