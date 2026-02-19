/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/19 14:24:47 by mleschev         ###   ########.fr       */
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
void verify_all(t_game **game_address)
{
	t_game *game = *game_address;

	if (game->map->ceilingColor[0] == -1 || game->map->ceilingColor[1] == -1 || game->map->ceilingColor[2] == -1)
	{
		printf("Error: color of ceiling\n");
		freeGame(game_address);
		exit (0);
	}
	if (game->map->floorColor[0] == -1 || game->map->floorColor[1] == -1 || game->map->floorColor[2] == -1)
	{
		printf("Error: color of floor\n");
		freeGame(game_address);
		exit (0);
	}
	if (!game->map->eastTexture || !game->map->northTexture || !game->map->southTexture || !game->map->westTexture) //rajouter voir si les textures sont accessibles
	{
		printf("Error: texture missing\n");
		freeGame(game_address);
		exit (0);
	}
	if (verif_map(game->map)) //fonction a rajouter mdrr
	{
		printf("Error: map not valid\n");
		freeGame(game_address);
		exit (0);
	}
}

int main(int argc, char **argv)
{
	t_game	*game;

	if (checkArg(argc, argv))
		return (1);

	game = malloc(sizeof(t_game));
	init_game(&game, argv[1]);


	// //printf debug ------------------------------------------------------------------------
	// printf("NO '%s'\nSO '%s'\nWE '%s'\nEA '%s'\nfC0 '%ld'\nfC1 '%ld'\nfC2 '%ld'\nCC0 '%ld'\nCC1 '%ld'\nCC2 '%ld'\nSTARTofMap '%d'\nENDofMap '%d'\n",
	// game->map->northTexture,
	// game->map->southTexture,
	// game->map->westTexture,
	// game->map->eastTexture,
	// game->map->floorColor[0],
	// game->map->floorColor[1],
	// game->map->floorColor[2],
	// game->map->ceilingColor[0],
	// game->map->ceilingColor[1],
	// game->map->ceilingColor[2],
	// game->map->startMapInReading,
	// game->map->LineOfEof);

	// printf("\n\nmap (%d):\n", game->map->readingHead);
	// int i = 0;
	// int j = 0;
	// while (game->map->mapChar[i])
	// {
	// 	j = 0;
	// 	printf(" '%s' ", game->map->mapChar[i]);
	// 	printf("\n");
	// 	i++;
	// }
	// // ------------------------------------------------------------------------
	verify_all(&game);



	init(game);
	return (0);
}
