/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:16:04 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 19:26:51 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int close_mlx(void *param)
{
	t_game *game = (t_game *)param;
	mlx_loop_end(game->mlx->mlx);
	mlx_clear_window(game->mlx->mlx, game->mlx->window);
	mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	mlx_destroy_display(game->mlx->mlx);
	free(game->mlx->mlx);
	return (1);
}

int	on_keypress(int key, void *game)
{
	if (key == 65307)
		close_mlx(game);
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
	game->img->img = mlx_new_image(game->mlx->mlx, x_win, y_win);
	game->img->addr = mlx_get_data_addr(
    		game->img->img,
        	&game->img->bpp,
        	&game->img->line_len,
        	&game->img->endian
		);
}

void	init(t_game *game)
{
	game->mlx->mlx = mlx_init();
	add_img(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, x_win, y_win, "ntr manu");
	mlx_hook(game->mlx->window, 2, (1L << 0), on_keypress, game);
	mlx_hook(game->mlx->window, 17, 0, close_mlx, game);
	mlx_loop(game->mlx->mlx);
}
