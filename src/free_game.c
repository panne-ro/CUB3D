/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:08:25 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/30 16:26:05 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	sub_free_map_copy_and_char(t_map *map)
{
	int	i;

	i = 0;
	if (map->copy_map)
	{
		while (map->copy_map[i])
		{
			free(map->copy_map[i]);
			i++;
		}
		free(map->copy_map);
	}
	if (map->map_char)
	{
		i = 0;
		while (map->map_char[i])
		{
			free(map->map_char[i]);
			i++;
		}
		free(map->map_char);
	}
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->fd_map >= 0)
		close(map->fd_map);
	if (map->east_texture)
		free(map->east_texture);
	if (map->west_texture)
		free(map->west_texture);
	if (map->north_texture)
		free(map->north_texture);
	if (map->south_texture)
		free(map->south_texture);
	sub_free_map_copy_and_char(map);
}

void	sub_free_game(t_game **game)
{
	t_game	*current;

	current = *game;
	if (current->player)
		free(current->player);
	if (current->tex_ea)
		free(current->tex_ea);
	if (current->tex_no)
		free(current->tex_no);
	if (current->tex_so)
		free(current->tex_so);
	if (current->tex_we)
		free(current->tex_we);
	if (*game)
		free(*game);
}

void	free_game(t_game **game)
{
	t_game	*current;

	current = *game;
	free_map(current->map);
	if (current->img)
		free(current->img);
	if (current->mlx)
		free(current->mlx);
	if (current->dda)
		free(current->dda);
	if (current->map)
		free(current->map);
	if (current->player && current->player->dir)
		free(current->player->dir);
	if (current->player && current->player->pos)
		free(current->player->pos);
	if (current->player && current->player->flags_moov)
		free(current->player->flags_moov);
	sub_free_game(game);
}
