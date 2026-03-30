/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:05:28 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/30 16:23:16 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img->addr + (y * game->img->line_len + x
			* (game->img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	int_ceiling_to_rgb(t_game *game)
{
	int	r;
	int	g;
	int	b;

	r = game->map->ceilling_color[0];
	g = game->map->ceilling_color[1];
	b = game->map->ceilling_color[2];
	return ((r << 16) | (g << 8) | b);
}

int	int_floor_to_rgb(t_game *game)
{
	int	r;
	int	g;
	int	b;

	r = game->map->floor_color[0];
	g = game->map->floor_color[1];
	b = game->map->floor_color[2];
	return ((r << 16) | (g << 8) | b);
}

void	add_colors(t_game *game)
{
	game->img->ceiling_color = int_ceiling_to_rgb(game);
	game->img->wall_color = 0x8B4513;
	game->img->floor_color = int_floor_to_rgb(game);
}
