/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_player_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:51:41 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/23 12:57:21 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	check_if_cant_go_w(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x + game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	dir_y = (dir_y + game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	if (game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}

bool	check_if_cant_go_s(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x - game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	dir_y = (dir_y - game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	if (game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}

bool	check_if_cant_go_a(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x + game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	dir_y = (dir_y - game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	if (game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}

bool	check_if_cant_go_d(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x - game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	dir_y = (dir_y + game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION + 0.1;
	if (game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}
