/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:01:00 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/27 11:34:56 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void refresh_map(t_game *game)
{
	mlx_clear_window(game->mlx->mlx, game->mlx->window);
	print_map(game);
}



// give a dir letter withe a game pointer return true if the position is a wall else if its ok
bool check_if_cant_go(char dir, t_game *game)
{
	int dir_x = ((int)game->player->pos->x + (int)game->player->dir->x) * MOVESPEED / 32;
	int dir_y = ((int)game->player->pos->y + (int)game->player->dir->y) * MOVESPEED / 32;

	if (dir)
	{
		printf("DEBUG: x:%d y:%d\n", dir_x, dir_y);
	}


	// if (dir == 'w')
	// {
	// 	if (!game->map->mapChar[(int)game->player->pos->y - MOVESPEED / MINIMAP_RESOLUTION][(int)game->player->pos->x / MINIMAP_RESOLUTION])
	// 		return false;
	// }
	// else if (dir == 's')
	// else if (dir == 'd')
	// else if (dir == 'a')
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
	else if (dir == 's' /*&& check_if_cant_go(dir, game)*/)
	{
		game->player->pos->x -= game->player->dir->x * MOVESPEED;
		game->player->pos->y -= game->player->dir->y * MOVESPEED;
	}
	else if (dir == 'a' /*&& check_if_cant_go(dir, game)*/)
	{
		game->player->pos->x += game->player->dir->y * MOVESPEED;
		game->player->pos->y -= game->player->dir->x * MOVESPEED;
	}
	else if (dir == 'd' /*&& check_if_cant_go(dir, game)*/)
	{
		game->player->pos->x -= game->player->dir->y * MOVESPEED;
		game->player->pos->y += game->player->dir->x * MOVESPEED;
	}
	refresh_map(game);
}

void moov_look_dir(t_game *game, char dir)
{
	if (dir == 'g')
		game->player->angle -= 0.1;
	else if (dir == 'd')
		game->player->angle += 0.1;
	game->player->dir->x = cos(game->player->angle);
	game->player->dir->y = sin(game->player->angle);
	game->player->plane.x = game->player->dir->y * FOV;
	game->player->plane.y = -game->player->dir->x * FOV;
	refresh_map(game);
}
