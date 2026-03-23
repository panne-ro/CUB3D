/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_player_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 19:51:41 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/23 15:51:06 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool x_max(char **map, int player_pos_y, int where_we_going)
{
	int x_max;

	x_max = 0;
	while (map[player_pos_y / MINIMAP_RESOLUTION][x_max])
		x_max++;
	if (x_max < where_we_going || where_we_going < 0)
		return false;
	return true;
}

bool y_max(char **map, int where_we_going)
{
	int y_max;

	y_max = 0;
	while (map[y_max])
		y_max++;
	if (y_max < where_we_going || where_we_going < 0)
		return false;
	return true;
}

bool	check_if_cant_go_w(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x + game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
	dir_y = (dir_y + game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;

	if (y_max(game->map->mapChar, dir_y) && x_max(game->map->mapChar, game->player->pos->y, dir_x) && game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}

bool	check_if_cant_go_s(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x - game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
	dir_y = (dir_y - game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;
	if (y_max(game->map->mapChar, dir_y) && x_max(game->map->mapChar, game->player->pos->y, dir_x) && game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}

bool	check_if_cant_go_a(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x + game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;
	dir_y = (dir_y - game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
	if (y_max(game->map->mapChar, dir_y) && x_max(game->map->mapChar, game->player->pos->y, dir_x) && game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}

bool	check_if_cant_go_d(t_game *game, int dir_x, int dir_y)
{
	dir_x = (dir_x - game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;
	dir_y = (dir_y + game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
	if (y_max(game->map->mapChar, dir_y) && x_max(game->map->mapChar, game->player->pos->y, dir_x) && game->map->mapChar[dir_y][dir_x] == '1')
		return (false);
	return (true);
}
