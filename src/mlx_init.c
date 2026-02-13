/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:16:04 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 17:51:29 by panne-ro         ###   ########.fr       */
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
	//if (key == 100)
		//move_right();
	return (0);
}

void    put_pixel(t_img *img, int x, int y, int color)
{
    char    *pixel;

    if (x < 0 || x >= x_win || y < 0 || y >= y_win)
        return;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}

void	add_img(t_game *game)
{
	game->img->img = mlx_new_image(game->mlx, x_win, y_win);
	game->img->addr = mlx_get_data_addr(
    		game->img->img,
        	&game->img->bpp,
        	&game->img->line_len,
        	&game->img->endian
		);
}

void	init(t_game *game)
{
	game->mlx = malloc(sizeof(t_mlx));
	game->img = malloc(sizeof(t_img));
	game->player = malloc(sizeof(t_player));
	game->mlx->mlx = mlx_init();
	add_img(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, x_win, y_win, "ntr manu");
	game->player = print_map(game);
	mlx_hook(game->mlx->window, 2, (1L << 0), on_keypress, game->mlx);
	mlx_hook(game->mlx->window, 17, 0, mlx_loop_end, game->mlx->mlx);
	mlx_loop(game->mlx->mlx);
	mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	mlx_destroy_display(game->mlx->mlx);
	free(game->img);
	free(game->mlx->mlx);
	free(game->mlx);
}
