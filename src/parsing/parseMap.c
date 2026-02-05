/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:15:12 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/05 22:21:44 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//check map in map file return a bool for error like:
//true = error find
//false = map is ok
bool checkMap(t_map *map, char *lineRead)
{
	int i;
	while (lineRead)
	{
		i = 0;
		while (lineRead[i] && map->startMapInReading == 0)
		{
			if (lineRead[i] != ' ' && lineRead[i] != '\n' && lineRead[i] != '\f' && lineRead[i] != '\r' && lineRead[i] != '\t' && lineRead[i] != '\n' && lineRead[i] != '\v')
				map->startMapInReading = map->readingHead;
			i++;
		}
		while (lineRead[i] && map->startMapInReading > 0)
		{
			if ((lineRead[i] != '1' && lineRead[i] != '0' && lineRead[i] != ' ' && lineRead[i] != '\n') || (i == 0 && (lineRead[i] == '\n' || lineRead[i] == '\0')))
				{
					printf("TEMP: Error map in map file invalid, i:%d, mapread:%d\n", i, map->readingHead); //temporaire
					return true;
				}
			i++;
		}
		lineRead = get_next_line(map->fdMap);
		map->readingHead++;
	}
	return false;
}

void putReadingHeadInPlace(t_map *map, char *lineRead)
{
	map->LineOfEof = map->readingHead;
	close(map->fdMap);
	map->fdMap = open(map->filePath, O_RDONLY);
	map->readingHead = 0;

	lineRead = get_next_line(map->fdMap);
	map->readingHead++;

	//on se remet a la bonne positions dans le fichier
	while (lineRead && map->readingHead < map->startMapInReading - 1)
	{
		lineRead = get_next_line(map->fdMap);
		map->readingHead++;
	}
}

// sub_function for parse map only in map file return in map->
void parseMap(t_map *map, char *lineRead)
{
	int i;
	int j;
	j = 0;

	//on cherche quand la map commence et la fin du fichier + check erreur sur la map
	if (checkMap(map, lineRead))
		return ;
	putReadingHeadInPlace(map, lineRead);

	map->mapInt = malloc(sizeof(int *) * (map->LineOfEof - map->startMapInReading + 1));
	if (!map->mapInt)
		printf("TEMP malloc parseMap.c defaut\n");//temp

	//on imprime la map dans map.mapInt
	while (lineRead && map->readingHead < map->LineOfEof)
	{
		i = 0;
		// printf("DEBUG : '%s' '%d'\n", lineRead, map->readingHead);
		while (lineRead[i])
		{
			i++;
		}
		map->mapInt[j] = malloc(sizeof(int) * (i + 1));
		i = 0;
		while (lineRead[i] && map->readingHead >= (map->startMapInReading && map->readingHead <= map->LineOfEof))
		{
			if (lineRead[i] == '1')
				map->mapInt[j][i] = 1;
			else if (lineRead[i] == '0')
				map->mapInt[j][i] = 0;
			else if (lineRead[i] == '\0' || lineRead[i] == '\n')
				map->mapInt[j][i] = -2;
			else
				map->mapInt[j][i] = -1;
			i++;
		}
		lineRead = get_next_line(map->fdMap);
		map->readingHead++;
		j++;
	}
	map->mapInt[j] = NULL;
}
