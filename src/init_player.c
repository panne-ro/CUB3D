/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:40:01 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 19:16:53 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_dir(t_game *game)
{
	if (game->map->start_dir == 'N')
	{
		game->player->dir.x = 0;
		game->player->dir.y = -1;
	}
	if (game->map->start_dir == 'S')
	{
		game->player->dir.x = 0;
		game->player->dir.y = 1;
	}
	if (game->map->start_dir == 'E')
	{
		game->player->dir.x = 1;
		game->player->dir.y = 0;
	}
	if (game->map->start_dir == 'W')
	{
		game->player->dir.x = -1;
		game->player->dir.y = 0;
	}
}

void	init_plane(t_game *game)
{
	game->player->plane.x = game->player->dir.x * 0.66;
	game->player->plane.y = (game->player->dir.y * -1) * 0.66;
}

void	init_player(t_game *game)
{
	game->player->pos.x = 9.5;
	game->player->pos.y = 4.5;
	init_dir(game);
	init_plane(game);
}