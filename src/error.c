/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:14:48 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/25 01:43:55 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	check_texture_file(t_game *game)
{
	int	fd_test;

	fd_test = open(game->map->eastTexture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	fd_test = open(game->map->westTexture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	fd_test = open(game->map->northTexture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	fd_test = open(game->map->southTexture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	return (false);
}

bool	check_range_color(t_game *game)
{
	if (game->map->floorColor[0] < 0 || game->map->floorColor[0] > 255)
		return (true);
	if (game->map->floorColor[1] < 0 || game->map->floorColor[1] > 255)
		return (true);
	if (game->map->floorColor[2] < 0 || game->map->floorColor[2] > 255)
		return (true);
	if (game->map->ceilingColor[0] < 0 || game->map->ceilingColor[0] > 255)
		return (true);
	if (game->map->ceilingColor[1] < 0 || game->map->ceilingColor[1] > 255)
		return (true);
	if (game->map->ceilingColor[2] < 0 || game->map->ceilingColor[2] > 255)
		return (true);
	if (game->map->valid_nbr_color == false)
		return (true);
	return (false);
}

void	close_all(t_game **game_address, char *msg)
{
	printf("DEBUG Error: %s\n", msg);
	free_game(game_address);
	exit (0);
}

void	verify_all(t_game **game_address)
{
	t_game	*game;

	game = *game_address;
	if (game->map->ceilingColor[0] == -1 || game->map->ceilingColor[1] == -1
		|| game->map->ceilingColor[2] == -1)
		close_all(game_address, "color of ceiling is missing");
	if (game->map->floorColor[0] == -1 || game->map->floorColor[1] == -1
		|| game->map->floorColor[2] == -1)
		close_all(game_address, "color of floor is missing");
	if (check_range_color(game))
		close_all(game_address,
			"color of ceiling or floor have invalidate format");
	if (!game->map->eastTexture || !game->map->northTexture
		|| !game->map->southTexture || !game->map->westTexture)
		close_all(game_address, "some texture is missing");
	if (check_texture_file(game))
		close_all(game_address, "file texture is invalidate");
	if (verif_map(game->map, 0, 0))
		close_all(game_address, "map format is not valid");
}
