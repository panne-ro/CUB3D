/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 14:32:18 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_game	*init_game(t_game *game)
{
	game->mlx = malloc(sizeof(t_mlx));
	game->img = malloc(sizeof(t_img));
	game->map = malloc(sizeof(t_map));
	game->player = malloc(sizeof(t_player));
}

void freeMap(t_map *map)
{
	int i = 0;
	// free(map->floorColor);
	// free(map->ceilingColor);
	free(map->eastTexture);
	free(map->westTexture);
	free(map->northTexture);
	free(map->southTexture);

	while (map->mapChar[i])
	{
		free(map->mapChar[i]);
		i++;
	}
	free(map->mapChar);
	// free(map->filePath);

	// free(map->fdMap);
	// free(map->floorColor);
	// free(map->startMapInReading);
	// free(map->heightOfMap);
	// free(map->LineOfEof);
}

int main(int argc, char **argv)
{
	if (checkArg(argc, argv) == 1)
		return (1);
	t_game	*game;
	game = malloc(sizeof(t_game));
	
	
	initMapStruct(game, argv[1]);
	init(game);
	freeMap(game->map);
	free(game->map);
	free(game);
	return (0);
}
