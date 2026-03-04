/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:26:03 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/04 17:45:42 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	dda(t_game *game)
{
	double posY = (double)game->player->pos->y / MINIMAP_RESOLUTION;
	double posX = (double)game->player->pos->x / MINIMAP_RESOLUTION;
	char *data = game->img->addr;
	for (int col = 0; col < x_win; ++col)
	{
		double cameraX = 2.0 * col / (double)x_win - 1.0;
		double ray_px_x = game->player->dir->x + game->player->plane.x * cameraX;
		double ray_px_y = game->player->dir->y + game->player->plane.y * cameraX;

		double dirX = ray_px_x;
		double dirY = ray_px_y;
		double deltaDistX;
		double deltaDistY;
		if (dirX == 0.0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1.0 / dirX);
		if (dirY == 0.0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1.0 / dirY);
		int mapX = (int)floor(posX);
		int mapY = (int)floor(posY);
		int stepX;
		int stepY;
		double sideDistX;
		double sideDistY;
		if (dirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (dirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		int hit = 0;
		int side = 0;
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapY < 0 || mapX < 0)
				break;
			if (!game->map->mapChar[mapY])
				break;
			if (mapX >= (int)ft_strlen(game->map->mapChar[mapY]))
				break;
			if (game->map->mapChar[mapY][mapX] == '1')
				hit = 1;
		}
		if (hit)
		{
			double perp;
			if (side == 0)
				perp = sideDistX - deltaDistX;
			else
				perp = sideDistY - deltaDistY;

			if (perp <= 1e-6)
				perp = 1e-6;
			int line_height = (int)((double)y_win / perp);
			int draw_start = -line_height / 2 + y_win / 2;
			if (draw_start < 0)
				draw_start = 0;
			int draw_end = line_height / 2 + y_win / 2;
			if (draw_end >= y_win)
				draw_end = y_win - 1;
			int ceiling_color = 0x87CEEB;
			int wall_color = 0x8B4513;
			int floor_color = 0x228B22;
			for (int y = 0; y < y_win; ++y)
			{
				int color;
				if (y < draw_start)
					color = ceiling_color;
				else if (y <= draw_end)
					color = wall_color;
				else
					color = floor_color;

				int offset = y * game->img->line_len + col * (game->img->bpp / 8);
				if (game->img->bpp == 32)
				{
					*(int *)(data + offset) = color;
				}
				else
				{
					if (offset + 2 < y_win * game->img->line_len && offset >= 0)
					{
						data[offset + 0] = (char)(color & 0xFF);
						data[offset + 1] = (char)((color >> 8) & 0xFF);
						data[offset + 2] = (char)((color >> 16) & 0xFF);
					}
				}
			}
		}
	}
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->img, 0, 0);
	return (0);
}
