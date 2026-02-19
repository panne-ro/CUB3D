/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/19 12:04:46 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


// take a *t_map, the path for map and init all the value at NULL or -1 and pass into checkmap()
void initMapStruct(t_game **gameAddr, char *pathToMap)
{
	int i;
	t_game *game;

	game = *gameAddr;
	i = 0;

	game->map->filePath = pathToMap;
	game->map->fdMap = -1;
	game->map->mapChar = NULL;
	game->map->readingHead = 0;

	while (i++ < 3)
	{
		game->map->ceilingColor[i] = -1;
		game->map->floorColor[i] = -1;
	}

	game->map->eastTexture = NULL;
	game->map->westTexture = NULL;
	game->map->northTexture = NULL;
	game->map->southTexture = NULL;

	game->map->startMapInReading = 0;
	game->map->LineOfEof = 0;

	game->map->isValid = false;
	game->map->isClosed = false;

	checkmap(gameAddr);
}


// take a t_map already init with initMapStruct() and check all the infos inside return an error with printf and -1 or 0 if all good
int checkmap(t_game **gameAddr)
{
	t_game *game;

	game = *gameAddr;
	game->map->fdMap = open(game->map->filePath, O_RDONLY);
	if (game->map->fdMap < 0)
	{
		printf("Error can't open map\n");
		freeGame(gameAddr);
		exit (1);
	}

	checkContentMaster(game->map);

	return 0;
}

// function for recall get_next_line into lineRead and change the \n to \0
char *readAndCleanLine(char *lineRead, t_map *map)
{
	int i;

	i = 0;
	lineRead = get_next_line(map->fdMap);
	if (!lineRead)
		return lineRead;
	map->readingHead++;
	while (lineRead[i])
	{
		if (lineRead[i] == '\n')
		{
			lineRead[i] = 0;
			break ;
		}
		i++;
	}
	return (lineRead);
}

// baise ta mere c'est ecrit dans le nom
int checkContentMaster(t_map *map)
{
	char tmp[1000];

	map->northTexture = checkContentNO(map, tmp);
	map->southTexture = checkContentSO(map, tmp);
	map->westTexture = checkContentWE(map, tmp);
	map->eastTexture = checkContentEA(map, tmp);
	checkContentFC(tmp, map);
	checkContentCC(tmp, map);
	parseMap(map);
	return 0;
}
//final check of mapChar for t_map *map
bool verif_map(t_map *map)
{
	int i;
	int j;
	int nbr_player;
	bool map_is_start;

	map_is_start = false;
	i = 0;
	nbr_player = 0;
	if (!map->mapChar)
		return true;
	while (map->mapChar[i])
	{
		j = 0;
		if (ft_strlen(map->mapChar[i]) == 0)
		{
			printf("ALED1");//debug
			return true;
		}
		//check si la map a deja commencer et si ele contient plusieurs 'fragment'
		if (!map_is_start && ft_strlen(map->mapChar[i]))
			map_is_start = true;
		if (map_is_start && ft_strlen(map->mapChar[i]) == 1 && map->mapChar[i][0] == '\n')
		{
			printf("ALED2");//debug
			return true;
		}
		while (map->mapChar[i][j])
		{
			//check si la map contient des valeurs inetrdites
			if ((map->mapChar[i][j] != '0' && map->mapChar[i][j] != '1') && (map->mapChar[i][j] != 'E' && map->mapChar[i][j] != 'W' && map->mapChar[i][j] != 'N' && map->mapChar[i][j] != 'S'))
			{
				printf("ALED3");//debug
				return true;
			}
			//check nombre de player
			if (map->mapChar[i][j] == 'E' || map->mapChar[i][j] == 'W' || map->mapChar[i][j] == 'N' || map->mapChar[i][j] == 'S')
				nbr_player++;
			j++;
		}
		i++;
	}
	if (nbr_player > 1)
	{
		printf("ALED4");//debug
		return true;
	}
	return false;
}
