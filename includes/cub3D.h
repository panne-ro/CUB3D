/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 16:52:52 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/30 16:31:25 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define X_WIN 1920
# define Y_WIN 1080

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>
# define PI 3.14159265359
# define MOVESPEED 10
# define FOV 0.6
# define MINIMAP_RESOLUTION 64
# define FPS 60

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"

// struct for map with all his data's like gov.site for j
typedef struct s_map
{
	int			fd_map;
	char		*file_path;

	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;

	long int	floor_color[3];
	bool		fc_taken;
	bool		is_fc;
	long int	ceilling_color[3];
	bool		cc_taken;
	bool		is_cc;

	int			height_of_map;
	int			line_of_eof;
	int			reading_head;
	int			start_map_in_reading;

	bool		is_closed;
	bool		is_valid;
	bool		boolean;
	bool		valid_nbr_color;

	float		player_x;
	float		player_y;

	char		**map_char;
	char		**copy_map;

	char		start_dir;
}	t_map;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_moov
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	look_right;
	int	look_left;
}	t_moov;

typedef struct s_player
{
	t_vector	*pos;
	t_vector	*dir;
	t_vector	plane;
	t_moov		*flags_moov;
	double		angle;
}	t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		ceiling_color;
	int		wall_color;
	int		floor_color;
}	t_img;

typedef struct s_dda
{
	double	pos_y;
	double	pos_x;
	int		hit;
	int		side;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		col;
	char	*data;
}	t_dda;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_tex;

typedef struct s_game
{
	long		last_time;
	long		current_time;
	double		delta_time;
	double		perp;
	int			line_height;
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_mlx		*mlx;
	t_dda		*dda;
	t_tex		*tex_no;
	t_tex		*tex_so;
	t_tex		*tex_we;
	t_tex		*tex_ea;
}	t_game;

// check_content_utils.c
void		check_content_cc(char *tmp, t_map *map, int i, char *line_read);
char		*copy_content(char *line_read, char *tmp, int i);
void		dispatch_color_at_good_place(t_map *map, char *tmp, int nbr);
int			rgb_dispatch_info_file(char *line_read, char *tmp,
				int i, t_map *map);
void		flush_and_reopen(t_map *map);

// parse_utils_second.c
int			sub_check_content_fc(char *tmp, t_map *map, int i, char *line_read);
int			sub_check_content_cc(char *tmp, t_map *map, int i, char *line_read);

// check_content.c
char		*check_content_no(char *tmp, int i, char*line_read);
char		*check_content_so(char *tmp, int i, char*line_read);
char		*check_content_we(char *tmp, int i, char*line_read);
char		*check_content_ea(char *tmp, int i, char*line_read);
void		check_content_fc(char *tmp, t_map *map, int i, char *line_read);

// check_map_utils.c
char		*read_and_clean_line(char *line_read, t_map *map);
bool		sub_loop_master_in_verif_map(t_map *map, int *i,
				int *j, int *nbr_player);
bool		sub_loop_verif_map(t_map *map, int *i, int *j, int *nbr_player);
int			check_flood_fill(t_map *map, int x, int y);
void		flood_fill(int x, int y, t_map *map);

// check_map.c
char		**copy_map(char **map);
void		init_map_struct(t_game **gameAddr, char *pathToMap);
int			checkmap(t_game **gameAddr);
int			return_of_the_token(char	*line_read);
int			return_of_the_value(char *line_read, int i);

// parse_utils.c
void		flush_gnl(int fd);
bool		check_double(char first, char second, t_map *map);
bool		check_double_master(t_map *map);
bool		check_color_format(char *line);
int			sub_ext_is_all_wall(t_map *map, int y, int x);

// parse_map.c
bool		check_map(t_map *map);
char		*put_reading_head_in_place(t_map *map);
void		sub_parse_map(char *line_read, t_map *map, int i, int j);
int			ext_is_all_wall(t_map *map);
void		parse_map(t_map *map);

// parsing_arg.c
int			check_arg(int argc, char **argv);
int			extension_check(char *str);

// error.c
bool		check_texture_file(t_game *game);
bool		check_range_color(t_game *game);
void		close_all(t_game **game_address, char *msg);
void		verify_all(t_game **game_address);

// free_game.c
void		sub_free_map_copy_and_char(t_map *map);
void		free_map(t_map *map);
void		sub_free_game(t_game **game);
void		free_game(t_game **game);

// init_player.c
void		init_var(t_game *game);
void		init_dir_and_plane(t_game *game);
void		init_flag_moov(t_game *game);
void		init_player(t_game *game);

// load_texture.c
void		init_all_texture(t_game **game_addr);
t_tex		*load_texture(void *mlx, char *path);
void		put_texture_on_wall(t_game *game, int y, int x);

// main.c
void		init_game(t_game **gameAddr, char *pathFile);
long		get_time(void);

// mlx_init.c
int			close_mlx(void *param);
int			key_release(int key, void *game);
int			on_keypress(int key, void *game);
int			update(void *game);
void		init(t_game **game_addr);

//  moov_player_dir.c
bool		y_max(char **map, int where_we_going);
bool		check_if_cant_go_w(t_game *game, int dir_x, int dir_y);
bool		check_if_cant_go_s(t_game *game, int dir_x, int dir_y);
bool		check_if_cant_go_a(t_game *game, int dir_x, int dir_y);
bool		check_if_cant_go_d(t_game *game, int dir_x, int dir_y);

// moov_player.c
bool		x_max(char **map, int player_pos_y, int where_we_going);
void		refresh_map(t_game *game);
bool		check_if_cant_go(char dir, t_game *game);
void		moov_player(t_game *game, char dir);
void		moov_look_dir(t_game *game, char dir);

// raycasting_utils.c
void		my_mlx_pixel_put(t_game *game, int x, int y, int color);
int			int_ceiling_to_rgb(t_game *game);
int			int_floor_to_rgb(t_game *game);
void		add_colors(t_game *game);

// raycasting.c
void		maj_var(t_game *game);
void		calc_dir(t_game *game, double dir_x, double dir_y);
void		calc_side(t_game *game);
void		print_world(t_game *game, int x);
int			dda(t_game *game);

// sub_moov_dir.c
void		sub_moov_w(t_game *game);
void		sub_moov_s(t_game *game);
void		sub_moov_d(t_game *game);
void		sub_moov_a(t_game *game);

// vector.c
t_vector	sum_vector(t_vector vector1, t_vector vector2);
t_vector	*sub_vector(t_vector *vector1, t_vector *vector2);
t_vector	mul_vector(t_vector vector, int scale);

// check_content_master.c
int			check_content_master(t_map *map);
bool		verif_map(t_map *map, int i, int nbr_player);
void		process_token(t_map *map, char *line_read, char tmp[1000], int i);
#endif
