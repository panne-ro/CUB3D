#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>

#include "./libft/libft.h"

int		extensionCheck(char *str);
int		checkArg(int argc, char **argv);

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

	int **mapInt;

} t_map;

// parsing:

void initMapStruct(t_map *map, char *pathToMapFile);
int checkContentMaster(t_map *map);
char *copyContent(char *lineRead, char *tmp, int i);

int checkmap(t_map *map);

// checkcontent.c

char *checkContentNO(t_map *map, char *tmp, char *lineRead);
char *checkContentSO(t_map *map, char *tmp, char *lineRead);
char *checkContentWE(t_map *map, char *tmp, char *lineRead);
char *checkContentEA(t_map *map, char *tmp, char *lineRead);

void checkContentFC(int fd, char *tmp, char *lineRead, t_map *map);
void checkContentCC(int fd, char *tmp, char *lineRead, t_map *map);
void rgbDispatchInfoFile(char *lineRead, char *tmp, int i, t_map *map, bool forCeiling);
void parseMap(t_map *map, char *lineRead);

#endif
