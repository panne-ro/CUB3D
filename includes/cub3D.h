#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"

typedef struct s_map
{
	int fdMap;
	char filePath;
	
	char *northTexture;
	char *southTexture;
	char *westTexture;
	char *eastTexture;
	
	size_t floorColor[3];
	size_t ceilingColor[3];
	
	size_t height;
	size_t size;
	
	bool isClosed;
	bool isCubMap;
	
} t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
} t_mlx;


// parsing:

void initMapStruct(t_map *map);

int		parse_extension(char *str);
int		parse(int argc, char **argv);