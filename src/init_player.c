/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:40:01 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/26 18:20:56 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_dir_and_plane(t_game *game)
{
	if (game->map->start_dir == 'N')
		game->player->angle = -PI / 2;
	if (game->map->start_dir == 'S')
		game->player->angle = PI / 2;
	if (game->map->start_dir == 'E')
		game->player->angle = 0;
	if (game->map->start_dir == 'W')
		game->player->angle = PI;
	game->player->dir->x = cos(game->player->angle);
	game->player->dir->y = sin(game->player->angle);
	game->player->plane.x = game->player->dir->y * FOV;
	game->player->plane.y = -game->player->dir->x * FOV;
}

void	init_player(t_game *game)
{
	game->player->pos = malloc(sizeof(t_vector));
	game->player->dir = malloc(sizeof(t_vector));
	game->player->pos->x = 10 * MINIMAP_RESOLUTION - MINIMAP_RESOLUTION / 2;
	game->player->pos->y = 7 * MINIMAP_RESOLUTION - MINIMAP_RESOLUTION / 2;
	init_dir_and_plane(game);
}
