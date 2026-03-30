/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:26:03 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/30 16:30:36 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	maj_var(t_game *game)
{
	game->dda->camera_x = 2.0 * game->dda->col / (double)X_WIN - 1.0;
	game->dda->dir_x = game->player->dir->x + game->player->plane.x
		* game->dda->camera_x;
	game->dda->dir_y = game->player->dir->y + game->player->plane.y
		* game->dda->camera_x;
	if (game->dda->dir_x == 0.0)
		game->dda->delta_dist_x = 1e30;
	else
		game->dda->delta_dist_x = fabs(1.0 / game->dda->dir_x);
	if (game->dda->dir_y == 0.0)
		game->dda->delta_dist_y = 1e30;
	else
		game->dda->delta_dist_y = fabs(1.0 / game->dda->dir_y);
	game->dda->map_x = (int)floor(game->dda->pos_x);
	game->dda->map_y = (int)floor(game->dda->pos_y);
}

void	calc_dir(t_game *game, double dir_x, double dir_y)
{
	if (dir_x < 0)
	{
		game->dda->step_x = -1;
		game->dda->side_dist_x = (game->dda->pos_x - game->dda->map_x)
			* game->dda->delta_dist_x;
	}
	else
	{
		game->dda->step_x = 1;
		game->dda->side_dist_x = (game->dda->map_x + 1.0 - game->dda->pos_x)
			* game->dda->delta_dist_x;
	}
	if (dir_y < 0)
	{
		game->dda->step_y = -1;
		game->dda->side_dist_y = (game->dda->pos_y - game->dda->map_y)
			* game->dda->delta_dist_y;
	}
	else
	{
		game->dda->step_y = 1;
		game->dda->side_dist_y = (game->dda->map_y + 1.0 - game->dda->pos_y)
			* game->dda->delta_dist_y;
	}
}

void	calc_side(t_game *game)
{
	while (!game->dda->hit)
	{
		if (game->dda->side_dist_x < game->dda->side_dist_y)
		{
			game->dda->side_dist_x += game->dda->delta_dist_x;
			game->dda->map_x += game->dda->step_x;
			game->dda->side = 0;
		}
		else
		{
			game->dda->side_dist_y += game->dda->delta_dist_y;
			game->dda->map_y += game->dda->step_y;
			game->dda->side = 1;
		}
		if (game->dda->map_y < 0 || game->dda->map_x < 0)
			break ;
		if (!game->map->map_char[game->dda->map_y])
			break ;
		if (game->dda->map_x >= (int)
			ft_strlen(game->map->map_char[game->dda->map_y]))
			break ;
		if (game->map->map_char[game->dda->map_y][game->dda->map_x] == '1')
			game->dda->hit = 1;
	}
}

void	print_world(t_game *game, int x)
{
	int	y;
	int	draw_start;
	int	draw_end;

	game->line_height = (int)((double)Y_WIN / game->perp);
	draw_end = game->line_height / 2 + Y_WIN / 2;
	draw_start = -game->line_height / 2 + Y_WIN / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= Y_WIN)
		draw_end = Y_WIN - 1;
	add_colors(game);
	y = 0;
	while (y < Y_WIN)
	{
		if (y < draw_start)
			my_mlx_pixel_put(game, x, y, game->img->ceiling_color);
		else if (y <= draw_end)
			put_texture_on_wall(game, y, x);
		else
			my_mlx_pixel_put(game, x, y, game->img->floor_color);
		y++;
	}
}

int	dda(t_game *game)
{
	init_var(game);
	while (game->dda->col < X_WIN)
	{
		maj_var(game);
		calc_dir(game, game->dda->dir_x, game->dda->dir_y);
		game->dda->hit = 0;
		calc_side(game);
		if (game->dda->hit)
		{
			game->perp = 0;
			if (game->dda->side == 0)
				game->perp = game->dda->side_dist_x - game->dda->delta_dist_x;
			else
				game->perp = game->dda->side_dist_y - game->dda->delta_dist_y;
			if (game->perp <= 1e-6)
				game->perp = 1e-6;
			print_world(game, game->dda->col);
		}
		game->dda->col++;
	}
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
		game->img->img, 0, 0);
	return (0);
}
