/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 00:05:29 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/18 00:15:16 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_all_texture(t_game **game_addr)
{
	t_game	*game;

	game = *game_addr;
	game->tex_no = load_texture(game->mlx->mlx, game->map->northTexture);
	game->tex_so = load_texture(game->mlx->mlx, game->map->southTexture);
	game->tex_we = load_texture(game->mlx->mlx, game->map->westTexture);
	game->tex_ea = load_texture(game->mlx->mlx, game->map->eastTexture);
	if (!game->tex_no || !game->tex_so || !game->tex_we || !game->tex_ea)
	{
		printf("Error: texture load failed\n");
		exit(1);
	}
}

t_tex	*load_texture(void *mlx, char *path)
{
	t_tex	*tex;

	tex = malloc(sizeof(t_tex));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (NULL);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
	return (tex);
}

// full chatgpt g rien compris + pas eu la fois whalla + ca marche pas g le mort
void	put_texture_on_wall(t_game *game, double perp, int line_height,
	int y, int x, int draw_start)
{
	double	wall_x;
	t_tex	*tex;
	int		tex_x;
	int		tex_y;
	int		color;

	if (game->dda->side == 0)
		wall_x = game->player->pos->y + perp * game->dda->dirY;
	else
		wall_x = game->player->pos->x + perp * game->dda->dirX;
	wall_x -= floor(wall_x);
	if (game->dda->side == 0 && game->dda->dirX > 0)
		tex = game->tex_we;
	else if (game->dda->side == 0 && game->dda->dirX < 0)
		tex = game->tex_ea;
	else if (game->dda->side == 1 && game->dda->dirY > 0)
		tex = game->tex_no;
	else
		tex = game->tex_so;
	tex_x = (int)(wall_x * tex->width);
	if ((game->dda->side == 0 && game->dda->dirX > 0)
		|| (game->dda->side == 1 && game->dda->dirY < 0))
		tex_x = tex->width - tex_x - 1;
	tex_y = (int)(((double)(y - draw_start) *tex->height) / line_height);
	color = *(unsigned int *)(tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
	my_mlx_pixel_put(game, x, y, color);
}
