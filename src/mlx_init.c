/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 19:16:04 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/04 11:50:13 by mleschev         ###   ########.fr       */
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
int key_release(int key, void *game)
{
	t_game *current = (t_game *)game;
	if (key == 119)
		current->player->flags_moov->w = 0;
	if (key == 115)
		current->player->flags_moov->s = 0;
	if (key == 97)
		current->player->flags_moov->a = 0;
	if (key == 100)
		current->player->flags_moov->d = 0;
	if (key == 65361)
		current->player->flags_moov->look_left = 0;
	if (key == 65363)
		current->player->flags_moov->look_right = 0;
	return (0);
}

int	on_keypress(int key, void *game)
{
	t_game *current = (t_game *)game;
	if (key == 65307)
		close_mlx(game);
	if (key == 119)
		current->player->flags_moov->w = 1;
	if (key == 115)
		current->player->flags_moov->s = 1;
	if (key == 97)
		current->player->flags_moov->a = 1;
	if (key == 100)
		current->player->flags_moov->d = 1;
	if (key == 65361)
		current->player->flags_moov->look_left = 1;
	if (key == 65363)
		current->player->flags_moov->look_right = 1;
	return (0);
}

int update(void *game)
{
	t_game *current = (t_game *)game;
	if (current->player->flags_moov->w)
		moov_player(game, 'w');
	if (current->player->flags_moov->s)
		moov_player(game, 's');
	if (current->player->flags_moov->a)
		moov_player(game, 'a');
	if (current->player->flags_moov->d)
		moov_player(game, 'd');
	if (current->player->flags_moov->look_left)
		moov_look_dir(game, 'g');
	if (current->player->flags_moov->look_right)
		moov_look_dir(game, 'd');
	refresh_map(game);
	return (0);
}

void	add_img(t_game *game)
{
	int x;

	x = 64;
	game->img->floor = mlx_xpm_file_to_image(game->mlx->mlx, "./space.xpm", &x, &x);
	game->img->wall = mlx_xpm_file_to_image(game->mlx->mlx, "./wall.xpm", &x, &x);
	game->img->gridsee = mlx_xpm_file_to_image(game->mlx->mlx, "./player.xpm", &x, &x);
}

void	init(t_game **game_addr)
{
	t_game *game = *game_addr;
	game->mlx->mlx = mlx_init();
	init_player(game);
	add_img(game);
	game->mlx->window = mlx_new_window(game->mlx->mlx, x_win, y_win, "ntr pablo");
	print_map(game);
	mlx_hook(game->mlx->window, 2, (1L << 0), on_keypress, game);
	mlx_hook(game->mlx->window, 3, (1L << 1), key_release, game);
	mlx_hook(game->mlx->window, 17, 0, close_mlx, game);
	mlx_loop_hook(game->mlx->mlx, update, game);
	mlx_loop(game->mlx->mlx);
}
