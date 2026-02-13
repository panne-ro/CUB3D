/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:26:03 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 19:28:05 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_sky_and_floor(t_game *game, float draw_start, float draw_end, int x, int side)
{
	int y = 0;

	while (y < draw_start)
	{
    	put_pixel(game->img, x, y, 0x87CEEB); // bleu ciel
    	y++;
	}
	while (y < draw_end)
	{
    	if (side == 1)
        	put_pixel(game->img, x, y, 0xAAAAAA); // mur plus sombre
    	else
        	put_pixel(game->img, x, y, 0xFFFFFF); // mur clair
    	y++;
	}
	while (y < y_win)
	{
    	put_pixel(game->img, x, y, 0x444444); // gris foncé
    	y++;
	}
}

void	calc_sidedist(t_game *game)
{
	if (game->dda->step->x == 1)
		game->dda->sidedist->x = (game->dda->map->x + 1 - game->player->pos.x) * game->dda->deltadist->x;
	else
		game->dda->sidedist->x = (game->player->pos.x - game->dda->map->x) * game->dda->deltadist->x;
	if (game->dda->step->y == 1)
		game->dda->sidedist->y = (game->dda->map->y + 1 - game->player->pos.y) * game->dda->deltadist->y;
	else
		game->dda->sidedist->y = (game->player->pos.y - game->dda->map->y) * game->dda->deltadist->y;
}

void	dda_init(t_game	*game, t_vector *raydir)
{
	game->dda->map->x = floor(game->player->pos.x);
	game->dda->map->y = floor(game->player->pos.y);
	if (raydir->x == 0)
    	game->dda->deltadist->x = 1e30;
	else
    	game->dda->deltadist->x = fabs(1 / raydir->x);
	if (raydir->y == 0)
    	game->dda->deltadist->y = 1e30;
	else
    	game->dda->deltadist->y = fabs(1 / raydir->y);
	if (raydir->x > 0)
		game->dda->step->x = 1;
	else
		game->dda->step->x = -1;
	if (raydir->y > 0)
		game->dda->step->y = 1;
	else
		game->dda->step->y = -1;
	calc_sidedist(game);
}

int	dda(t_game *game)
{
	int	side;
	
	while(1)
	{
		if (game->dda->sidedist->x < game->dda->sidedist->y)
		{
			game->dda->sidedist->x += game->dda->deltadist->x;
			game->dda->map->x += game->dda->step->x;
			side = 0;
		}
		else
		{
			game->dda->sidedist->y += game->dda->deltadist->y;
			game->dda->map->y += game->dda->step->y;
			side = 1;
		}
		int mx = (int)game->dda->map->x;
		int my = (int)game->dda->map->y;
		if (my < 0 || my >= game->map->heightOfMap)
    		return side;
		int line_len = strlen(game->map->mapChar[my]);
		if (mx < 0 || mx >= line_len)
    	{
			game->dda->map->x -= game->dda->step->x; 
			game->dda->map->y -= game->dda->step->y;
			return (side);
		}
		if (game->map->mapChar[my][mx] == '1')
    		return side;
	}
}

void	raycasting(t_game *game)
{
	float		cameraX;
	t_vector	raydir;
	int 		x;
	int			side;
	float		WallDist;
	float		line_height;
	float		draw_start;
	float		draw_end;

	x = 0;
	while (x < x_win)
	{
		cameraX = 2.0f * x / (float)x_win - 1.0f;
		raydir = sum_vector(game->player->dir, mul_vector(game->player->plane, cameraX));
		dda_init(game, &raydir);
		side = dda(game);
		if (side == 0)
			WallDist = (game->dda->map->x - game->player->pos.x + (1 - game->dda->step->x)/2) / raydir.x;
		else
    		WallDist = (game->dda->map->y - game->player->pos.y + (1 - game->dda->step->y)/2) / raydir.y;
		line_height = y_win / WallDist;
		draw_start = -line_height/2 + y_win/2;
		draw_end = line_height/2 + y_win/2;
		print_sky_and_floor(game, draw_start, draw_end, x, side);
		x++;
	}
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->img, 0, 0);
}
