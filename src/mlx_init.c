/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:16:04 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/09 16:03:17 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_map(t_mlx *mlx, t_img *imgs, char **map)
{
	int i;
	int j = 0;
	int x;
	int y = 0;

	if (!map)
		return;

	while (map[j])
	{
		x = 0;
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '1')
			{
				if (imgs->wall)
					mlx_put_image_to_window(mlx->mlx, mlx->window, imgs->wall, x, y);
			}
			else if (map[j][i] == '0')
			{
				if (imgs->space)
					mlx_put_image_to_window(mlx->mlx, mlx->window, imgs->space, x, y);
			}
			else
			{
				if (imgs->player)
					mlx_put_image_to_window(mlx->mlx, mlx->window, imgs->player, x, y);
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

void	init(char **map)
{
	t_mlx	*mlx;
	t_img	*imgs;

	mlx = malloc(sizeof(t_mlx));
	imgs = malloc(sizeof(t_img));
	mlx->mlx = mlx_init();
	imgs = add_img(mlx, imgs);
	mlx->window = mlx_new_window(mlx->mlx, x_win, y_win, "ntr manu");
	print_map(mlx, imgs, map);
	mlx_hook(mlx->window, 17, 0, mlx_loop_end,mlx->mlx);
	mlx_loop(mlx->mlx);
	destroy_img(mlx, imgs);
	mlx_destroy_window(mlx->mlx, mlx->window);
	free(imgs);
	free(mlx);
}
