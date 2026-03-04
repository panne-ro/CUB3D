/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:14:48 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/04 15:44:48 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void freeMap(t_map *map)
{
	int i = 0;

	if (!map)
		return ;
	if (map->eastTexture)
		free(map->eastTexture);
	if (map->westTexture)
		free(map->westTexture);
	if (map->northTexture)
		free(map->northTexture);
	if (map->southTexture)
		free(map->southTexture);
	if (!map->mapChar)
		return ;
	while (map->mapChar[i])
	{
		free(map->mapChar[i]);
		i++;
	}
	free(map->mapChar);

}

void freeGame(t_game **game)
{
	t_game *current;
	current = *game;

	freeMap(current->map);
	if (current->img)
		free(current->img);
	if (current->mlx)
		free(current->mlx);
	if (current->map)
		free(current->map);
	if (current->player && current->player->dir)
		free(current->player->dir);
	if (current->player->pos)
		free(current->player->pos);
	if (current->player->flags_moov)
		free(current->player->flags_moov);
	if (current->player)
		free(current->player);
	if (*game)
		free(*game);
}

bool check_texture_file(t_game *game)
{
	int fd_test;

	fd_test = open(game->map->eastTexture, O_RDONLY);
	if (fd_test < 0)
		return true;
	close(fd_test);
	fd_test = open(game->map->westTexture, O_RDONLY);
	if (fd_test < 0)
		return true;
	close(fd_test);
	fd_test = open(game->map->northTexture, O_RDONLY);
	if (fd_test < 0)
		return true;
	close(fd_test);
	fd_test = open(game->map->southTexture, O_RDONLY);
	if (fd_test < 0)
		return true;
	close(fd_test);
	return false;
}

bool check_range_color(t_game *game)
{
	if (game->map->floorColor[0] < 0 || game->map->floorColor[0] > 255)
		return true;
	if (game->map->floorColor[1] < 0 || game->map->floorColor[1] > 255)
		return true;
	if (game->map->floorColor[2] < 0 || game->map->floorColor[2] > 255)
		return true;
	if (game->map->ceilingColor[0] < 0 || game->map->ceilingColor[0] > 255)
		return true;
	if (game->map->ceilingColor[1] < 0 || game->map->ceilingColor[1] > 255)
		return true;
	if (game->map->ceilingColor[2] < 0 || game->map->ceilingColor[2] > 255)
		return true;
	return false;
}

void verify_all(t_game **game_address)
{
	t_game *game = *game_address;

	if (game->map->ceilingColor[0] == -1 || game->map->ceilingColor[1] == -1 || game->map->ceilingColor[2] == -1)
	{
		printf("Error: color of ceiling is missing\n");
		freeGame(game_address);
		exit (0);
	}
	if (game->map->floorColor[0] == -1 || game->map->floorColor[1] == -1 || game->map->floorColor[2] == -1)
	{
		printf("Error: color of floor is missing\n");
		freeGame(game_address);
		exit (0);
	}
	if (check_range_color(game))
	{
		printf("Error: color of floor or ceiling is not in range\n");
		freeGame(game_address);
		exit (0);
	}
	if (!game->map->eastTexture || !game->map->northTexture || !game->map->southTexture || !game->map->westTexture)
	{
		printf("Error: texture missing in %s\n", game->map->filePath);
		freeGame(game_address);
		exit (0);
	}
	if (check_texture_file(game)) //voir si les textures sont des fichier valides
	{
		printf("Error: texture file not valid\n");
		freeGame(game_address);
		exit (0);
	}
	if (verif_map(game->map))
	{
		printf("Error: map not valid\n");
		freeGame(game_address);
		exit (0);
	}
}
