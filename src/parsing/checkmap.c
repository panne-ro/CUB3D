/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/04 00:20:40 by mleschev         ###   ########.fr       */
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
	map->matriceIntMap = NULL;

	while (i++ < 3)
	{
		map->ceilingColor[i] = -1;
		map->floorColor[i] = -1;
	}

	map->eastTexture = NULL;
	map->westTexture = NULL;
	map->northTexture = NULL;
	map->southTexture = NULL;

	map->height = -1;
	map->size = -1;

	map->isCubMap = false;
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

// baise ta mere c'est ecrit dans le nom
int checkContentMaster(t_map *map)
{
	char tmp[1000];
	char *lineRead;

	lineRead = get_next_line(map->fdMap);

	map->northTexture = checkContentNO(map->fdMap, tmp, lineRead);
	map->southTexture = checkContentSO(map->fdMap, tmp, lineRead);
	map->westTexture = checkContentWE(map->fdMap, tmp, lineRead);
	map->eastTexture = checkContentEA(map->fdMap, tmp, lineRead);
	checkContentFC(map->fdMap, tmp, lineRead, map);

	printf("NO '%s'\nSO '%s'\nWE '%s'\nEA '%s'\nCC0 '%ld'\nCC1 '%ld'\nCC2 '%ld'\n", 
	map->northTexture,
	map->southTexture,
	map->westTexture,
	map->eastTexture,
	map->floorColor[0],
	map->floorColor[1],
	map->floorColor[2]);


	return 0;
}