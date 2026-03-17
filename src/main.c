/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/17 23:46:52 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_game(t_game **gameAddr, char *pathFile)
{
	t_game	*current;

	current = *gameAddr;
	current->mlx = malloc(sizeof(t_mlx));
	current->img = malloc(sizeof(t_img));
	current->map = malloc(sizeof(t_map));
	current->dda = malloc(sizeof(t_dda));
	current->player = malloc(sizeof(t_player));
	current->player->pos = malloc(sizeof(t_vector));
	current->player->dir = malloc(sizeof(t_vector));
	current->player->flags_moov = malloc(sizeof(t_moov));
	current->map->copy_map = NULL;
	init_map_struct(gameAddr, pathFile);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (check_arg(argc, argv))
		return (1);
	game = malloc(sizeof(t_game));
	init_game(&game, argv[1]);
	verify_all(&game);
	init(&game);
	mlx_loop(game->mlx->mlx);
	return (0);
}
