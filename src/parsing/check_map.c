/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/23 19:16:09 by panne-ro         ###   ########.fr       */
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
	game->map->valid_nbr_color = true;
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
bool	verif_map(t_map *map, int i, int nbr_player)
{
	int		j;
	int y = map->player_y;
	int x = map->player_x;

	if (!map->mapChar)
		return (true);
	if (sub_loop_master_in_verif_map(map, &i, &j, &nbr_player) == true)
		return (true);
	if (nbr_player > 1 || !nbr_player)
		return (true);
	if (!map->copy_map)
		map->copy_map = copy_map(map->mapChar);
	flood_fill(x, y, map);
	if (map->isClosed == false)
		return (true);
	return (false);
}
