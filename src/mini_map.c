/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:51:06 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/03 15:32:41 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_map(t_game *game)
{
	int	x;
	int	y;
	int w;
	int	h;

	x = 0;
	h = 0;
	while(game->map->mapChar[x])
	{
		y = 0;
		w = 0;
		while(game->map->mapChar[x][y])
		{
			if(game->map->mapChar[x][y] == '0')
				mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->floor, w, h);
			else if (game->map->mapChar[x][y] == '1')
				mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->wall, w, h);
			w += 64;
			y++;
		}
		h += 64;
		x++;
	}
	int m = -6;
	while(m <= 5)
	{
		int n = -6;
		while (n <= 5)
		{
			mlx_pixel_put(game->mlx->mlx, game->mlx->window, game->player->pos->x + n, game->player->pos->y + m, 250);
			n++;
		}
		m++;
	}
	dda(game);
	
	double left_x  = game->player->dir->x - game->player->plane.x;
	double left_y  = game->player->dir->y - game->player->plane.y;
	double right_x = game->player->dir->x + game->player->plane.x;
	double right_y = game->player->dir->y + game->player->plane.y;
	for (int i = 0; i < 200; i++)
	{
		mlx_pixel_put(game->mlx->mlx, game->mlx->window,
			game->player->pos->x + left_x * i,
			game->player->pos->y + left_y * i,
			0x00FF00); // vert

		mlx_pixel_put(game->mlx->mlx, game->mlx->window,
			game->player->pos->x + right_x * i,
			game->player->pos->y + right_y * i,
			0x0000FF); // bleu
	}
}
