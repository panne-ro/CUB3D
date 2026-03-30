/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/30 16:26:05 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// take a *t_map, the path for map and init all the value at NULL
//or -1 and pass into checkmap()
void	init_map_struct(t_game **gameAddr, char *pathToMap)
{
	int		i;
	t_game	*game;

	game = *gameAddr;
	i = 0;
	game->map->file_path = pathToMap;
	game->map->fd_map = -1;
	game->map->map_char = NULL;
	game->map->reading_head = 0;
	while (i < 3)
	{
		game->map->ceilling_color[i] = -1;
		game->map->floor_color[i] = -1;
		i++;
	}
	game->map->east_texture = NULL;
	game->map->west_texture = NULL;
	game->map->north_texture = NULL;
	game->map->south_texture = NULL;
	game->map->start_map_in_reading = 0;
	game->map->line_of_eof = 0;
	game->map->valid_nbr_color = true;
	game->map->is_valid = false;
	game->map->is_closed = false;
	checkmap(gameAddr);
}

// take a t_map already init with init_map_struct() and check all the infos
//inside return an error with printf and -1 or 0 if all good
int	checkmap(t_game **gameAddr)
{
	t_game	*game;

	game = *gameAddr;
	game->map->fd_map = open(game->map->file_path, O_RDONLY);
	if (game->map->fd_map < 0)
		close_all(gameAddr, "can't open map");
	if (check_double_master(game->map))
		close_all(gameAddr, "doublon file detected");
	check_content_master(game->map);
	return (0);
}

int	return_of_the_value(char *line_read, int i)
{
	if (line_read[i] && line_read[i] == 'N' && line_read[i + 1]
		&& line_read[i + 1] == 'O')
		return (1);
	else if (line_read[i] && line_read[i] == 'S' && line_read[i + 1]
		&& line_read[i + 1] == 'O')
		return (2);
	else if (line_read[i] && line_read[i] == 'W' && line_read[i + 1]
		&& line_read[i + 1] == 'E')
		return (3);
	else if (line_read[i] && line_read[i] == 'E' && line_read[i + 1]
		&& line_read[i + 1] == 'A')
		return (4);
	else if (line_read[i] && line_read[i] == 'F' && line_read[i + 1]
		&& line_read[i + 1] == ' ')
		return (5);
	else if (line_read[i] && line_read[i] == 'C' && line_read[i + 1]
		&& line_read[i + 1] == ' ')
		return (6);
	return (0);
}

int	return_of_the_token(char	*line_read)
{
	int		i;
	int		value_return;

	i = 0;
	value_return = 0;
	while (line_read[i])
	{
		value_return = return_of_the_value(line_read, i);
		if (value_return)
			return (value_return);
		i++;
	}
	return (0);
}
