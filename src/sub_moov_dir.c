/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_moov_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 00:00:34 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/18 00:03:43 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	sub_moov_w(t_game *game)
{
	game->player->pos->x += game->player->dir->x * MOVESPEED
		* game->delta_time;
	game->player->pos->y += game->player->dir->y * MOVESPEED
		* game->delta_time;
}

void	sub_moov_s(t_game *game)
{
	game->player->pos->x -= game->player->dir->x * MOVESPEED
		* game->delta_time;
	game->player->pos->y -= game->player->dir->y * MOVESPEED
		* game->delta_time;
}

void	sub_moov_d(t_game *game)
{
	game->player->pos->x -= game->player->dir->y * MOVESPEED
		* game->delta_time;
	game->player->pos->y += game->player->dir->x * MOVESPEED
		* game->delta_time;
}

void	sub_moov_a(t_game *game)
{
	game->player->pos->x += game->player->dir->y * MOVESPEED
		* game->delta_time;
	game->player->pos->y -= game->player->dir->x * MOVESPEED
		* game->delta_time;
}
