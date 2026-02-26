/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:40:01 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/26 10:25:41 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_dir(t_game *game)
{
	if (game->map->start_dir == 'N')
	{
		game->player->dir->x = 0;
		game->player->dir->y = -1;
	}
	if (game->map->start_dir == 'S')
	{
		game->player->dir->x = 0;
		game->player->dir->y = 1;
	}
	if (game->map->start_dir == 'E')
	{
		game->player->dir->x = 1;
		game->player->dir->y = 0;
	}
	if (game->map->start_dir == 'W')
	{
		game->player->dir->x = -1;
		game->player->dir->y = 0;
	}
}

void	init_plane(t_game *game)
{
	game->player->plane.x = game->player->dir->x * 0.66;
	game->player->plane.y = (game->player->dir->y * -1) * 0.66;
}

void	init_player(t_game *game)
{
	game->player->pos = malloc(sizeof(t_vector *));
	game->player->dir = malloc(sizeof(t_vector *));
	game->player->pos->x = 10 * 64 - 32;
	game->player->pos->y = 7 * 64 - 32;
	init_dir(game);
	init_plane(game);
}
