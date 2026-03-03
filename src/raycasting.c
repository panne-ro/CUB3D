/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:26:03 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/03 15:32:56 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	dda(t_game *game)
{
	int x = game->player->pos->x;
	int y = game->player->pos->y;

	
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->gridsee, (x / MINIMAP_RESOLUTION * MINIMAP_RESOLUTION), (y / MINIMAP_RESOLUTION * MINIMAP_RESOLUTION));
	float px = game->player->pos->x;
	float py = game->player->pos->y;
		// int i = 0;
for (int col = 0; col < x_win; ++col)
{
    double cameraX = 2.0 * col / (double)x_win - 1.0;
    double rayX = game->player->dir->x + game->player->plane.x * cameraX;
    double rayY = game->player->dir->y + game->player->plane.y * cameraX;
    float max_dist = 2000.0f;
    float step = 2.0f;
    for (float s = step; s < max_dist; s += step)
    {
        int cx = (int)floorf((px + rayX * s) / 64.0f);
        int cy = (int)floorf((py + rayY * s) / 64.0f);
        if (cy < 0 || cx < 0) break;
        if (!game->map->mapChar[cy]) break;
        if (cx >= (int)ft_strlen(game->map->mapChar[cy])) break;
        if (game->map->mapChar[cy][cx] != '0')
        {
            mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
                game->img->gridsee, cx * 64, cy * 64);
            break;
        }
    }
}
/*
		while (i < 700)
		{
			mlx_pixel_put(game->mlx->mlx, game->mlx->window, game->player->pos->x + game->player->dir->x * i, game->player->pos->y + game->player->dir->y * i, 0xFF0000);
			i++;
		}*/
	return (0);
}