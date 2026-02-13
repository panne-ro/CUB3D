/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:14:48 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/13 18:26:08 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void freeMap(t_map *map)
{
	int i = 0;

	if (map->eastTexture)
		free(map->eastTexture);
	if (map->westTexture)
		free(map->westTexture);
	if (map->northTexture)
		free(map->northTexture);
	if (map->southTexture)
		free(map->southTexture);
	if (!map->mapChar)
		return ;
	while (map->mapChar[i])
	{
		free(map->mapChar[i]);
		i++;
	}
	free(map->mapChar);

}

void freeGame(t_game **game)
{
	t_game *current;

	current = *game;

	freeMap(current->map);
	if (current->img)
		free(current->img);
	if (current->mlx)
	{
		// if (current->mlx->mlx)
		// 	free(current->mlx->mlx);
		free(current->mlx);
	}
	if (current->map)
		free(current->map);
	if (current->player)
		free(current->player);
	if (*game)
		free(*game);
}
