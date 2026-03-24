/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:40:01 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/24 13:39:03 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_var(t_game *game)
{
	game->dda->col = 0;
	game->dda->posY = (double)game->player->pos->y / MINIMAP_RESOLUTION;
	game->dda->posX = (double)game->player->pos->x / MINIMAP_RESOLUTION;
	game->dda->data = game->img->addr;
}

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
	game->player->plane.x = -game->player->dir->y * FOV;
	game->player->plane.y = game->player->dir->x * FOV;
}

void	init_flag_moov(t_game *game)
{
	game->player->flags_moov->a = 0;
	game->player->flags_moov->w = 0;
	game->player->flags_moov->s = 0;
	game->player->flags_moov->d = 0;
	game->player->flags_moov->look_left = 0;
	game->player->flags_moov->look_right = 0;
}

void	init_player(t_game *game)
{
	game->player->pos->x = game->map->player_x * MINIMAP_RESOLUTION;
	game->player->pos->y = game->map->player_y * MINIMAP_RESOLUTION;
	init_flag_moov(game);
	init_dir_and_plane(game);
}
