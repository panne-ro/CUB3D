/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:16:04 by panne-ro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/02/20 15:02:37 by mleschev         ###   ########.fr       */
=======
/*   Updated: 2026/02/25 19:06:03 by panne-ro         ###   ########.fr       */
>>>>>>> Pbranch
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int close_mlx(void *param)
{
	t_game *game = (t_game *)param;
	mlx_destroy_image(game->mlx->mlx, game->img->floor);
	mlx_destroy_image(game->mlx->mlx, game->img->wall);
	mlx_clear_window(game->mlx->mlx, game->mlx->window);
	mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	mlx_destroy_display(game->mlx->mlx);
	free(game->mlx->mlx);
	freeGame(&game);
	exit (0);
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

/*void    put_pixel(t_img *img, int x, int y, int color)
{
    char    *pixel;

    if (x < 0 || x >= x_win || y < 0 || y >= y_win)
        return;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)pixel = color;
}*/

void	add_img(t_game *game)
{
	int x;

	x = 64;
	game->img->floor = mlx_xpm_file_to_image(game->mlx->mlx, "./space.xpm", &x, &x);
	game->img->wall = mlx_xpm_file_to_image(game->mlx->mlx, "./wall.xpm", &x, &x);
}

void	init(t_game *game)
{
	game->mlx->mlx = mlx_init();
	init_player(game);
<<<<<<< HEAD
	printf("x = %f y = %f\n", game->player->dir->x, game->player->dir->y);
=======
>>>>>>> Pbranch
	add_img(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, x_win, y_win, "ntr manu");
	print_map(game);
	mlx_hook(game->mlx->window, 2, (1L << 0), on_keypress, game->mlx);
	mlx_hook(game->mlx->window, 17, 0, mlx_loop_end, game->mlx->mlx);
	mlx_loop(game->mlx->mlx);
	mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	mlx_destroy_display(game->mlx->mlx);
	free(game->player->pos);
	free(game->player->dir);
}
