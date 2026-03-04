#ifndef CUB3D_H
# define CUB3D_H

# define x_win 1920
# define y_win 1080

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <math.h>
#define PI 3.14159265359
#define MOVESPEED 15
#define FOV 0.6
#define MINIMAP_RESOLUTION 64

#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"

// TANG = OPP / ADJ
// SIN = OPP / HYP
// COS = ADJ / HYP

// struct for map with all his data's like gov.site for j
typedef struct s_map
{
	int fdMap;
	char *filePath;

	char *northTexture;
	char *southTexture;
	char *westTexture;
	char *eastTexture;

	long int floorColor[3];
	long int ceilingColor[3];

	int heightOfMap;
	int LineOfEof;
	int readingHead;
	int startMapInReading;


	bool isClosed;
	bool isValid;

	float player_x;
	float player_y;

	char **mapChar;

	char start_dir;

} t_map;

typedef struct s_vector
{
	float	x;
	float	y;
} t_vector;

typedef struct s_moov
{
	int	w;
	int	s;
	int	a;
	int d;
	int look_right;
	int look_left;
} t_moov;

typedef struct s_player
{
	t_vector	*pos;
	t_vector	*dir;
	t_vector	plane;
	t_moov		*flags_moov;
	double		angle;
} t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
} t_mlx;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*gridsee;
}   t_img;

typedef struct s_game
{
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_mlx		*mlx;
} t_game;

// parsing:
int		extensionCheck(char *str);
int		checkArg(int argc, char **argv);

void initMapStruct(t_game **gameAddr, char *pathToMapFile);
int checkContentMaster(t_map *map);
char *copyContent(char *lineRead, char *tmp, int i);

int checkmap(t_game **gameAddr);

// checkcontent.c

char *checkContentNO(t_map *map, char *tmp);
char *checkContentSO(t_map *map, char *tmp);
char *checkContentWE(t_map *map, char *tmp);
char *checkContentEA(t_map *map, char *tmp);

void checkContentFC(char *tmp, t_map *map);
void checkContentCC(char *tmp, t_map *map);
void rgbDispatchInfoFile(char *lineRead, char *tmp, int i, t_map *map, bool forCeiling);
void parseMap(t_map *map);

char *readAndCleanLine(char *lineRead, t_map *map);

//test
void init(t_game **game);
bool verif_map(t_map *map);

t_vector	sum_vector(t_vector vector1, t_vector vector2);
t_vector	*sub_vector(t_vector *vector1, t_vector *vector2);
t_vector	mul_vector(t_vector vector, int scale);
//  error.c
void verify_all(t_game **game_address);
void freeGame(t_game **game);
void freeMap(t_map *map);
bool check_range_color(t_game *game);
bool check_texture_file(t_game *game);

// void	raycasting(t_game *game);

void	init_player(t_game *game);

// void    put_pixel(t_img *img, int x, int y, int color);

void	print_map(t_game *game);

// moov_player.c
void	moov_player(t_game *game, char dir);
void	moov_look_dir(t_game *game, char dir);

int	dda(t_game *game);
int key_release(int key, void *game);
void refresh_map(t_game *game);


# endif
