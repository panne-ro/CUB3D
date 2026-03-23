/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moov_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:01:00 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/23 11:00:30 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	refresh_map(t_game *game)
{
	game->current_time = get_time();
	game->delta_time = (game->current_time - game->last_time) / 50.0;
	game->last_time = game->current_time;
	dda(game);
}

// give a dir letter withe a game pointer return falsw if the position is a wall
//and true if its ok
bool	check_if_cant_go(char dir, t_game *game)
{
	int	dir_x;
	int	dir_y;

	dir_x = game->player->pos->x + (game->player->dir->x * MOVESPEED);
	dir_y = game->player->pos->y + (game->player->dir->y * MOVESPEED);
	if (dir == 'w')
		return (check_if_cant_go_w(game, dir_x, dir_y));
	if (dir == 's')
		return (check_if_cant_go_s(game, dir_x, dir_y));
	else if (dir == 'd')
		return (check_if_cant_go_d(game, dir_x, dir_y));
	else if (dir == 'a')
		return (check_if_cant_go_a(game, dir_x, dir_y));
	return (true);
}

void	moov_player(t_game *game, char dir)
{
	if (dir == 'w' && check_if_cant_go(dir, game))
		sub_moov_w(game);
	else if (dir == 's' && check_if_cant_go(dir, game))
		sub_moov_s(game);
	else if (dir == 'a' && check_if_cant_go(dir, game))
		sub_moov_a(game);
	else if (dir == 'd' && check_if_cant_go(dir, game))
		sub_moov_d(game);
}

void	moov_look_dir(t_game *game, char dir)
{
	if (dir == 'g')
		game->player->angle -= 0.1 * game->delta_time;
	else if (dir == 'd')
		game->player->angle += 0.1 * game->delta_time;
	game->player->angle = fmod(game->player->angle, 2 * PI);
	if (game->player->angle < 0)
		game->player->angle += 2 * PI;
	game->player->dir->x = cos(game->player->angle);
	game->player->dir->y = sin(game->player->angle);
	game->player->plane.x = -game->player->dir->y * FOV;
	game->player->plane.y = game->player->dir->x * FOV;
}
