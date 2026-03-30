/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:14:48 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/30 16:23:16 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	check_texture_file(t_game *game)
{
	int	fd_test;

	fd_test = open(game->map->east_texture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	fd_test = open(game->map->west_texture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	fd_test = open(game->map->north_texture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	fd_test = open(game->map->south_texture, O_RDONLY);
	if (fd_test < 0)
		return (true);
	close(fd_test);
	return (false);
}

bool	check_range_color(t_game *game)
{
	if (game->map->floor_color[0] < 0 || game->map->floor_color[0] > 255)
		return (true);
	if (game->map->floor_color[1] < 0 || game->map->floor_color[1] > 255)
		return (true);
	if (game->map->floor_color[2] < 0 || game->map->floor_color[2] > 255)
		return (true);
	if (game->map->ceilling_color[0] < 0 || game->map->ceilling_color[0] > 255)
		return (true);
	if (game->map->ceilling_color[1] < 0 || game->map->ceilling_color[1] > 255)
		return (true);
	if (game->map->ceilling_color[2] < 0 || game->map->ceilling_color[2] > 255)
		return (true);
	if (game->map->valid_nbr_color == false)
		return (true);
	return (false);
}

void	close_all(t_game **game_address, char *msg)
{
	printf("DEBUG Error:\n%s\n", msg);
	free_game(game_address);
	exit (0);
}

void	verify_all(t_game **game_address)
{
	t_game	*game;

	game = *game_address;
	if (game->map->ceilling_color[0] == -1 || game->map->ceilling_color[1] == -1
		|| game->map->ceilling_color[2] == -1)
		close_all(game_address, "color of ceiling is missing");
	if (game->map->floor_color[0] == -1 || game->map->floor_color[1] == -1
		|| game->map->floor_color[2] == -1)
		close_all(game_address, "color of floor is missing");
	if (check_range_color(game))
		close_all(game_address,
			"color of ceiling or floor have invalidate format");
	if (!game->map->east_texture || !game->map->north_texture
		|| !game->map->south_texture || !game->map->west_texture)
		close_all(game_address, "some texture is missing");
	if (check_texture_file(game))
		close_all(game_address, "file texture is invalidate");
	if (verif_map(game->map, 0, 0))
		close_all(game_address, "map format is not valid");
}
