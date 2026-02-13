/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 18:40:33 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_game(t_game **gameAddr, char *pathFile)
{
	t_game *current;

	current = *gameAddr;
	current->mlx = malloc(sizeof(t_mlx));
	current->img = malloc(sizeof(t_img));
	current->map = malloc(sizeof(t_map));
	current->player = malloc(sizeof(t_player));

	initMapStruct(gameAddr, pathFile);
}

int main(int argc, char **argv)
{
	t_game	*game;

	if (checkArg(argc, argv))
		return (1);

	game = malloc(sizeof(t_game));
	init_game(&game, argv[1]);
	init(game);

	freeGame(&game);

	return (0);
}
