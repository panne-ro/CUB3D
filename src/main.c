/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/25 13:09:14 by vboxuser         ###   ########.fr       */
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
	current->mlx = calloc(1, sizeof(t_mlx));
	current->mlx->img = NULL;
	current->mlx->mlx = NULL;
	current->mlx->window = NULL;
	current->img = calloc(1, sizeof(t_img));
	current->map = calloc(1, sizeof(t_map));
	current->dda = calloc(1, sizeof(t_dda));
	current->player = calloc(1, sizeof(t_player));
	current->player->pos = calloc(1, sizeof(t_vector));
	current->player->dir = calloc(1, sizeof(t_vector));
	current->player->flags_moov = calloc(1, sizeof(t_moov));
	current->tex_ea = NULL;
	current->tex_no = NULL;
	current->tex_so = NULL;
	current->tex_we = NULL;
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
	return (0);
}
