#ifndef CUB3D_H
# define CUB3D_H

# define x_win 1920
# define y_win 1010

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"

// struct for map with all his data's like gov.site for j
typedef struct s_map
{
	int fdMap;
	char *filePath;

	char *northTexture;
	char *southTexture;
	char *westTexture;
	char *eastTexture;

	size_t floorColor[3];
	size_t ceilingColor[3];

	size_t heightOfMap;
	int LineOfEof;
	int readingHead;
	int startMapInReading;

	bool isClosed;
	bool isValid;

	char **mapChar;

} t_map;

typedef struct s_vector
{
	float	x;
	float	y;
} t_vector;

typedef struct s_player
{
	float	x;
	float	y;
} t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	void	*img;
} t_mlx;

typedef struct s_img
{
	void	*space;
	void	*wall;
	void	*player;
} t_img;

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

void initMapStruct(t_game *game, char *pathToMapFile);
int checkContentMaster(t_map *map);
char *copyContent(char *lineRead, char *tmp, int i);

int checkmap(t_map *map);

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
void init(char **map);

# endif
