/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:01:00 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/04 17:13:57 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void refresh_map(t_game *game)
{
	//mlx_clear_window(game->mlx->mlx, game->mlx->window);
	dda(game);
	//print_map(game);
}

// give a dir letter withe a game pointer return falsw if the position is a wall and true if its ok
bool check_if_cant_go(char dir, t_game *game)
{
	int dir_x = game->player->pos->x + (game->player->dir->x * MOVESPEED);
	int dir_y = game->player->pos->y + (game->player->dir->y * MOVESPEED);

	if (dir == 'w')
	{
		dir_x = (dir_x + game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
		dir_y = (dir_y + game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;
		if (game->map->mapChar[dir_y][dir_x] == '1')
			return false;
	}
	if (dir == 's')
	{
		dir_x = (dir_x - game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
		dir_y = (dir_y - game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;
		if (game->map->mapChar[dir_y][dir_x] == '1')
			return false;
	}
	else if (dir == 'd')
	{
		dir_x = (dir_x - game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;
		dir_y = (dir_y + game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
		if (game->map->mapChar[dir_y][dir_x] == '1')
			return false;
	}
	else if (dir == 'a')
	{
		dir_x = (dir_x + game->player->dir->y * MOVESPEED) / MINIMAP_RESOLUTION;
		dir_y = (dir_y - game->player->dir->x * MOVESPEED) / MINIMAP_RESOLUTION;
		if (game->map->mapChar[dir_y][dir_x] == '1')
			return false;
	}
	return true;
}

void	moov_player(t_game *game, char dir)
{
	// printf("X:%f Y:%f\n", game->player->pos->x, game->player->pos->y);
	if (dir == 'w' && check_if_cant_go(dir, game))
	{
		game->player->pos->x += game->player->dir->x * MOVESPEED;
		game->player->pos->y += game->player->dir->y * MOVESPEED;
	}
	else if (dir == 's' && check_if_cant_go(dir, game))
	{
		game->player->pos->x -= game->player->dir->x * MOVESPEED;
		game->player->pos->y -= game->player->dir->y * MOVESPEED;
	}
	else if (dir == 'a' && check_if_cant_go(dir, game))
	{
		game->player->pos->x += game->player->dir->y * MOVESPEED;
		game->player->pos->y -= game->player->dir->x * MOVESPEED;
	}
	else if (dir == 'd' && check_if_cant_go(dir, game))
	{
		game->player->pos->x -= game->player->dir->y * MOVESPEED;
		game->player->pos->y += game->player->dir->x * MOVESPEED;
	}
}

void moov_look_dir(t_game *game, char dir)
{
	if (dir == 'g')
		game->player->angle -= 0.1;
	else if (dir == 'd')
		game->player->angle += 0.1;
	game->player->angle = fmod(game->player->angle, 2 * PI);
	if (game->player->angle < 0)
		game->player->angle += 2 * PI;
	game->player->dir->x = cos(game->player->angle);
	game->player->dir->y = sin(game->player->angle);
	game->player->plane.x = -game->player->dir->y * FOV;
	game->player->plane.y = game->player->dir->x * FOV;
	
	refresh_map(game);
}
