/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 00:05:29 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/30 16:30:14 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_all_texture(t_game **game_addr)
{
	t_game	*game;

	game = *game_addr;
	game->tex_no = load_texture(game->mlx->mlx, game->map->north_texture);
	game->tex_so = load_texture(game->mlx->mlx, game->map->south_texture);
	game->tex_we = load_texture(game->mlx->mlx, game->map->west_texture);
	game->tex_ea = load_texture(game->mlx->mlx, game->map->east_texture);
	if (!game->tex_no || !game->tex_so || !game->tex_we || !game->tex_ea)
		close_all(game_addr, "texture load failed");
}

t_tex	*load_texture(void *mlx, char *path)
{
	t_tex	*tex;

	tex = malloc(sizeof(t_tex));
	if (!tex)
		return (NULL);
	tex->width = 64;
	tex->height = 64;
	tex->img = mlx_xpm_file_to_image(mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
	return (tex);
}

void	sub_put_texture_on_wall(t_game *game, int y, int x, t_tex	*tex)
{
	int	d;

	d = (y * 256) - (Y_WIN * 128) + (game->line_height * 128);
	tex->tex_y = (d * tex->height) / game->line_height / 256;
	if (tex->tex_y < 0)
		tex->tex_y = 0;
	if (tex->tex_y >= tex->height)
		tex->tex_y = tex->height - 1;
	tex->color = *(unsigned int *)(tex->addr
			+ (tex->tex_y * tex->line_len + tex->tex_x * (tex->bpp / 8)));
	my_mlx_pixel_put(game, x, y, tex->color);
}

void	put_texture_on_wall(t_game *game, int y, int x)
{
	double	wall_x;
	t_tex	*tex;

	if (game->dda->side == 0)
		wall_x = game->dda->pos_y + game->perp * game->dda->dir_y;
	else
		wall_x = game->dda->pos_x + game->perp * game->dda->dir_x;
	wall_x -= floor(wall_x);
	if (game->dda->side == 0 && game->dda->dir_x > 0)
		tex = game->tex_ea;
	else if (game->dda->side == 0 && game->dda->dir_x < 0)
		tex = game->tex_we;
	else if (game->dda->side == 1 && game->dda->dir_y > 0)
		tex = game->tex_so;
	else
		tex = game->tex_no;
	tex->tex_x = (int)(wall_x * tex->width);
	if ((game->dda->side == 0 && game->dda->dir_x < 0)
		|| (game->dda->side == 1 && game->dda->dir_y > 0))
		tex->tex_x = tex->width - tex->tex_x - 1;
	sub_put_texture_on_wall(game, y, x, tex);
}
