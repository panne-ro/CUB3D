/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:08:25 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/25 01:34:56 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (map->fdMap >= 0)
		close(map->fdMap);
	if (map->eastTexture)
		free(map->eastTexture);
	if (map->westTexture)
		free(map->westTexture);
	if (map->northTexture)
		free(map->northTexture);
	if (map->southTexture)
		free(map->southTexture);
	if (map->copy_map)
	{
		while (map->copy_map[i])
		{
			free(map->copy_map[i]);
			i++;
		}
		free(map->copy_map);
	}
	if (map->mapChar)
	{
		i = 0;
		while (map->mapChar[i])
		{
			free(map->mapChar[i]);
			i++;
		}
		free(map->mapChar);
	}
}


void	free_game(t_game **game)
{
	t_game	*current;

	current = *game;
	free_map(current->map);
	if (current->img)
		free(current->img);
	if (current->mlx) free(current->mlx);
	if (current->dda) free(current->dda);
	if (current->map) free(current->map);
	if (current->player && current->player->dir)
		free(current->player->dir);
	if (current->player && current->player->pos)
		free(current->player->pos);
	if (current->player && current->player->flags_moov)
		free(current->player->flags_moov);
	if (current->player) free(current->player);
	if (current->tex_ea) free(current->tex_ea);
	if (current->tex_no) free(current->tex_no);
	if (current->tex_so) free(current->tex_so);
	if (current->tex_we) free(current->tex_we);
	if (*game) free(*game);
}
