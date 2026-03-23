/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:26:03 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/17 17:53:12 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	maj_var(t_game *game)
{
	game->dda->cameraX = 2.0 * game->dda->col / (double)X_WIN - 1.0;
	game->dda->dirX = game->player->dir->x + game->player->plane.x
		* game->dda->cameraX;
	game->dda->dirY = game->player->dir->y + game->player->plane.y
		* game->dda->cameraX;
	if (game->dda->dirX == 0.0)
		game->dda->deltaDistX = 1e30;
	else
		game->dda->deltaDistX = fabs(1.0 / game->dda->dirX);
	if (game->dda->dirY == 0.0)
		game->dda->deltaDistY = 1e30;
	else
		game->dda->deltaDistY = fabs(1.0 / game->dda->dirY);
	game->dda->mapX = (int)floor(game->dda->posX);
	game->dda->mapY = (int)floor(game->dda->posY);
}

void	calc_dir(t_game *game, double dirX, double dirY)
{
	if (dirX < 0)
	{
		game->dda->stepX = -1;
		game->dda->sideDistX = (game->dda->posX - game->dda->mapX)
			* game->dda->deltaDistX;
	}
	else
	{
		game->dda->stepX = 1;
		game->dda->sideDistX = (game->dda->mapX + 1.0 - game->dda->posX)
			* game->dda->deltaDistX;
	}
	if (dirY < 0)
	{
		game->dda->stepY = -1;
		game->dda->sideDistY = (game->dda->posY - game->dda->mapY)
			* game->dda->deltaDistY;
	}
	else
	{
		game->dda->stepY = 1;
		game->dda->sideDistY = (game->dda->mapY + 1.0 - game->dda->posY)
			* game->dda->deltaDistY;
	}
}

void	calc_side(t_game *game)
{
	while (!game->dda->hit)
	{
		if (game->dda->sideDistX < game->dda->sideDistY)
		{
			game->dda->sideDistX += game->dda->deltaDistX;
			game->dda->mapX += game->dda->stepX;
			game->dda->side = 0;
		}
		else
		{
			game->dda->sideDistY += game->dda->deltaDistY;
			game->dda->mapY += game->dda->stepY;
			game->dda->side = 1;
		}
		if (game->dda->mapY < 0 || game->dda->mapX < 0)
			break ;
		if (!game->map->mapChar[game->dda->mapY])
			break ;
		if (game->dda->mapX >= (int)
			ft_strlen(game->map->mapChar[game->dda->mapY]))
			break ;
		if (game->map->mapChar[game->dda->mapY][game->dda->mapX] == '1')
			game->dda->hit = 1;
	}
}

void	print_world(t_game *game, double perp, int x)
{
	int	y;
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (int)((double)Y_WIN / perp);
	draw_end = line_height / 2 + Y_WIN / 2;
	draw_start = -line_height / 2 + Y_WIN / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= Y_WIN)
		draw_end = Y_WIN - 1;
	add_colors(game);
	y = 0;
	while (y <= Y_WIN)
	{
		if (y < draw_start)
			my_mlx_pixel_put(game, x, y, game->img->ceiling_color);
		else if (y <= draw_end)
			my_mlx_pixel_put(game, x, y, game->img->wall_color);
		else
			my_mlx_pixel_put(game, x, y, game->img->floor_color);
		y++;
	}
}

int	dda(t_game *game)
{
	double	perp;

	init_var(game);
	while (game->dda->col < X_WIN)
	{
		maj_var(game);
		calc_dir(game, game->dda->dirX, game->dda->dirY);
		game->dda->hit = 0;
		calc_side(game);
		if (game->dda->hit)
		{
			perp = 0;
			if (game->dda->side == 0)
				perp = game->dda->sideDistX - game->dda->deltaDistX;
			else
				perp = game->dda->sideDistY - game->dda->deltaDistY;
			if (perp <= 1e-6)
				perp = 1e-6;
			print_world(game, perp, game->dda->col);
		}
		game->dda->col++;
	}
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
		game->img->img, 0, 0);
	return (0);
}
