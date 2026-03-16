/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/16 16:25:01 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// flemme de le coder jsp si ca marche inch
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
		printf("%s\n", copy[i]);
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
	game->map->filePath = pathToMap;
	game->map->fdMap = -1;
	game->map->mapChar = NULL;
	game->map->readingHead = 0;
	while (i++ < 3)
	{
		game->map->ceilingColor[i] = -1;
		game->map->floorColor[i] = -1;
	}
	game->map->eastTexture = NULL;
	game->map->westTexture = NULL;
	game->map->northTexture = NULL;
	game->map->southTexture = NULL;
	game->map->startMapInReading = 0;
	game->map->LineOfEof = 0;
	game->map->isValid = false;
	game->map->isClosed = false;
	checkmap(gameAddr);
}

// take a t_map already init with init_map_struct() and check all the infos
//inside return an error with printf and -1 or 0 if all good
int	checkmap(t_game **gameAddr)
{
	t_game	*game;

	game = *gameAddr;
	game->map->fdMap = open(game->map->filePath, O_RDONLY);
	if (game->map->fdMap < 0)
	{
		printf("Error can't open map\n");
		free_game(gameAddr);
		exit (1);
	}
	check_content_master(game->map);
	return (0);
}

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

// baise ta mere c'est ecrit dans le nom
int	check_content_master(t_map *map)
{
	char	*line_read;
	char	tmp[1000];
	int		i;

	line_read = NULL;
	i = -1;
	map->northTexture = check_content_no(map, tmp, i);
	map->southTexture = check_content_so(map, tmp, i);
	map->westTexture = check_content_we(map, tmp, i);
	map->eastTexture = check_content_ea(map, tmp, i);
	check_content_fc(tmp, map, i, line_read);
	check_content_cc(tmp, map, i, line_read);
	parse_map(map);
	return (0);
}

//final check of mapChar for t_map *map
bool	verif_map(t_map *map)
{
	int		i;
	int		j;
	int		nbr_player;
	bool	map_is_start;

	map_is_start = false;
	i = 0;
	nbr_player = 0;
	if (!map->mapChar)
	{
		printf("error1\n");
		return (true);
	}
	while (map->mapChar[i])
	{
		j = 0;
		if (ft_strlen(map->mapChar[i]) == 0)
		{
			printf("error2\n");
			return (true);
		}
		map->isClosed = true;
		if (!map_is_start && ft_strlen(map->mapChar[i]))
			map_is_start = true;
		if (map_is_start && ft_strlen(map->mapChar[i]) == 1
			&& map->mapChar[i][0] == '\n')
		{
			printf("error3.1\n");
			return (true);
		}
		while (map->mapChar[i][j])
		{
			if ((map->mapChar[i][j] != '0' && map->mapChar[i][j] != '1')
				&& map->mapChar[i][j] != ' ' && (map->mapChar[i][j] != 'E'
				&& map->mapChar[i][j] != 'W' && map->mapChar[i][j] != 'N'
				&& map->mapChar[i][j] != 'S'))
			{
				printf("error3.2\n");
				return (true);
			}
			if (map->mapChar[i][j] == 'E' || map->mapChar[i][j] == 'W'
				|| map->mapChar[i][j] == 'N' || map->mapChar[i][j] == 'S')
			{
				map->player_x = j;
				map->player_y = i;
				map->start_dir = map->mapChar[i][j];
				nbr_player++;
			}
			j++;
		}
		i++;
	}
	if (nbr_player > 1 || !nbr_player)
	{
		printf("error4\n");
		return (true);
	}
	if (!map->copy_map)
		map->copy_map = copy_map(map->mapChar);
	flood_fill(map, map->player_x, map->player_y);
	if (!map->isClosed)
	{
		printf("error floodfill\n");
		return (true);
	}
	return (false);
}

void	flood_fill(t_map *map, int x, int y)
{
	if (y < 0 || x < 0)
	{
		map->isClosed = false;
		printf("stop flood at %d %d\n", x, y);
		return ;
	}
	if (!map->copy_map[y])
	{
		map->isClosed = false;
		printf("stop flood at %d %d\n", x, y);
		return ;
	}
	if (x >= (int)ft_strlen(map->copy_map[y]))
	{
		map->isClosed = false;
		printf("stop flood at %d %d\n", x, y);
		return ;
	}
	if (map->copy_map[y][x] == ' ')
	{
		map->isClosed = false;
		printf("stop flood at %d %d\n", x, y);
		return ;
	}
	if (map->copy_map[y][x] == '1' || map->copy_map[y][x] == 'F')
		return ;
	if (map->copy_map[y][x] == 'N'
		|| map->copy_map[y][x] == 'S'
		|| map->copy_map[y][x] == 'E'
		|| map->copy_map[y][x] == 'W')
		map->copy_map[y][x] = '0';
	map->copy_map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}
