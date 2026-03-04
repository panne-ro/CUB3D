/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:40:01 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/04 16:57:09 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_dir_and_plane(t_game *game)
{
	if (game->map->start_dir == 'N')
		game->player->angle = PI / 2;
	if (game->map->start_dir == 'S')
		game->player->angle = -PI / 2;
	if (game->map->start_dir == 'E')
		game->player->angle = 0;
	if (game->map->start_dir == 'W')
		game->player->angle = PI;
	game->player->dir->x = cos(game->player->angle);
	game->player->dir->y = sin(game->player->angle);
	game->player->plane.x = -game->player->dir->y * FOV;
	game->player->plane.y = game->player->dir->x * FOV;
}

void	init_player(t_game *game)
{
	game->player->pos = malloc(sizeof(t_vector));
	game->player->dir = malloc(sizeof(t_vector));
	game->player->pos->x = game->map->player_x * MINIMAP_RESOLUTION;
	game->player->pos->y = game->map->player_y * MINIMAP_RESOLUTION;
	printf("%f, %f\n", game->player->pos->x, game->player->pos->y);
	init_dir_and_plane(game);
}
