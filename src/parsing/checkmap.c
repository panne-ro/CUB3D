/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/06 17:06:22 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


// take a *t_map, the path for map and init all the value at NULL or -1
void initMapStruct(t_map *map, char *pathToMap)
{
	int i;
	i = 0;

	map->filePath = pathToMap;
	map->fdMap = -1;
	map->mapChar = NULL;
	map->readingHead = 0;

	while (i++ < 3)
	{
		map->ceilingColor[i] = -1;
		map->floorColor[i] = -1;
	}

	map->eastTexture = NULL;
	map->westTexture = NULL;
	map->northTexture = NULL;
	map->southTexture = NULL;

	map->startMapInReading = 0;
	map->LineOfEof = 0;

	map->isValid = false;
	map->isClosed = false;
}


// take a t_map already init with initMapStruct() and check all the infos inside return an error with printf and -1 or 0 if all good
int checkmap(t_map *map)
{
	map->fdMap =  open(map->filePath, O_RDONLY);

	if (map->fdMap < 0)
	{
		printf("Error can't open map\n");
		return -1;
	}

	checkContentMaster(map);

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
	char *lineRead;

	lineRead = NULL;
	lineRead = readAndCleanLine(lineRead, map);
	map->northTexture = checkContentNO(map, tmp, lineRead);
	map->southTexture = checkContentSO(map, tmp, lineRead);
	map->westTexture = checkContentWE(map, tmp, lineRead);
	map->eastTexture = checkContentEA(map, tmp, lineRead);
	checkContentFC(tmp, lineRead, map);
	checkContentCC(tmp, lineRead, map);
	lineRead = readAndCleanLine(lineRead, map);
	parseMap(map, lineRead);

	//printf debug ------------------------------------------------------------------------
	printf("NO '%s'\nSO '%s'\nWE '%s'\nEA '%s'\nfC0 '%ld'\nfC1 '%ld'\nfC2 '%ld'\nCC0 '%ld'\nCC1 '%ld'\nCC2 '%ld'\nSTARTofMap '%d'\nENDofMap '%d'\n",
	map->northTexture,
	map->southTexture,
	map->westTexture,
	map->eastTexture,
	map->floorColor[0],
	map->floorColor[1],
	map->floorColor[2],
	map->ceilingColor[0],
	map->ceilingColor[1],
	map->ceilingColor[2],
	map->startMapInReading,
	map->LineOfEof);

	printf("\n\nmap (%d):\n", map->readingHead);
	int i = 0;
	int j = 0;
	while (map->mapChar[i])
	{
		j = 0;
		printf(" '%s' ", map->mapChar[i]);
		printf("\n");
		i++;
	}
	// ------------------------------------------------------------------------

	return 0;
}
