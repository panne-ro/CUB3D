/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:15:12 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/30 16:26:05 by panne-ro         ###   ########.fr       */
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
		while (line_read[i] && map->start_map_in_reading == 0)
		{
			if (line_read[i] != ' ' && line_read[i] != '\n'
				&& line_read[i] != '\f' && line_read[i] != '\r'
				&& line_read[i] != '\t' && line_read[i] != '\n'
				&& line_read[i] != '\v')
				map->start_map_in_reading = map->reading_head;
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
	map->line_of_eof = map->reading_head;
	flush_gnl(map->fd_map);
	close(map->fd_map);
	map->fd_map = open(map->file_path, O_RDONLY);
	map->reading_head = 0;
	line_read = read_and_clean_line(line_read, map);
	while (line_read && map->reading_head < map->start_map_in_reading)
	{
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
	return (line_read);
}

void	sub_parse_map(char *line_read, t_map *map, int i, int j)
{
	line_read = put_reading_head_in_place(map);
	map->map_char = malloc(sizeof(char *)
			* (map->line_of_eof - map->start_map_in_reading + 2));
	map->height_of_map = map->line_of_eof - map->start_map_in_reading + 1;
	while (line_read)
	{
		i = 0;
		while (line_read[i])
			i++;
		map->map_char[j] = malloc(sizeof(char) * (i + 2));
		i = 0;
		while (line_read[i])
		{
			map->map_char[j][i] = line_read[i];
			i++;
		}
		map->map_char[j][i] = '\0';
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
		j++;
	}
	map->map_char[j] = NULL;
	free(line_read);
}

int	ext_is_all_wall(t_map *map)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	while (map->map_char[0][x])
	{
		if (map->map_char[0][x] == '0')
			return (0);
		x++;
	}
	while (map->map_char[y + 1])
		y++;
	x = 0;
	while (map->map_char[y][x])
	{
		if (map->map_char[y][x] == '0')
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
