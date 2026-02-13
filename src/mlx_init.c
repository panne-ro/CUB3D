/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:16:04 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 14:37:42 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	on_keypress(int key, t_mlx *mlx)
{
	if (key == 65307)
		mlx_loop_end(mlx->mlx);
	if (key == 119)
		printf("W");
	if (key == 115)
		printf("S");
	if (key == 97)
		printf("A");
	if (key == 100)
		move_right();
	return (0);
}

t_player	*print_map(t_game *game)
{
	int i;
	int j = 0;
	int x;
	int y = 0;

	if (!game->map->mapChar)
		return;
	while (game->map->mapChar[j])
	{
		x = 0;
		i = 0;
		while (game->map->mapChar[j][i])
		{
			if (game->map->mapChar[j][i] == '1')
				mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->wall, x, y);
			else if (game->map->mapChar[j][i] == '0')
				mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->space, x, y);
			else
			{
				mlx_put_image_to_window(game->mlx->mlx, game->mlx->window, game->img->player, x, y);
				game->player->x = x + 32;
				game->player->y = y + 32;
			}
			i++;
			x += 64;
		}
		j++;
		y += 64;
	}
}

void	destroy_img(t_mlx *mlx, t_img *imgs)
{
	if (imgs->player)
		mlx_destroy_image(mlx->mlx, imgs->player);
	if (imgs->wall)
		mlx_destroy_image(mlx->mlx, imgs->wall);
	if (imgs->space)
		mlx_destroy_image(mlx->mlx, imgs->space);
}

t_img	*add_img(t_mlx *mlx, t_img *imgs)
{
	int w = 32;
	int h = 32;

	imgs->wall = mlx_xpm_file_to_image(mlx->mlx, "./wall.xpm", &w, &h);
	imgs->space = mlx_xpm_file_to_image(mlx->mlx, "./space.xpm", &w, &h);
	imgs->player = mlx_xpm_file_to_image(mlx->mlx, "./player.xpm", &w, &h);
	if (!imgs->wall || !imgs->space || !imgs->player)
	{
		fprintf(stderr, "add_img: one or more images failed to load: wall=%p space=%p player=%p\n",
				imgs->wall, imgs->space, imgs->player);
	}
	return (imgs);
}

void	init(t_game *game)
{
	game->mlx = malloc(sizeof(t_mlx));
	game->img = malloc(sizeof(t_img));
	game->player = malloc(sizeof(t_player));
	game->mlx->mlx = mlx_init();
	game->img = add_img(game->mlx, game->img);
	game->mlx->window = mlx_new_window(game->mlx->mlx, x_win, y_win, "ntr manu");
	game->player = print_map(game);
	mlx_hook(game->mlx->window, 2, (1L << 0), on_keypress, game->mlx);
	mlx_hook(game->mlx->window, 17, 0, mlx_loop_end, game->mlx->mlx);
	mlx_loop(game->mlx->mlx);
	destroy_img(game->mlx, game->img);
	mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	mlx_destroy_display(game->mlx->mlx);
	free(game->img);
	free(game->mlx->mlx);
	free(game->mlx);
}
