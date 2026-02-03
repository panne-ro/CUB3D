#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#include "./libft/libft.h"

int		parse_extension(char *str);
int		parse(int argc, char **argv);


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

// parsing:

void initMapStruct(t_map *map);
