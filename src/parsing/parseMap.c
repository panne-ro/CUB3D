/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseMap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:15:12 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/13 15:47:36 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//check map in map file return a bool for error like:
//true = error find
//false = map is ok
bool checkMap(t_map *map)
{
	int i;
	int test;
	test = 0;
	char *lineRead = NULL;

	lineRead = readAndCleanLine(lineRead, map);
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
			if ((lineRead[i] != '1' && lineRead[i] != '0' && lineRead[i] != 'S' && lineRead[i] != 'W' && lineRead[i] != 'E' && lineRead[i] != 'N' && lineRead[i] != ' ' && lineRead[i] != '\n') || (i == 0 && (lineRead[i] == '\n' || lineRead[i] == '\0')))
			{
				printf("TEMP: Error map in map file invalid, i:%d, mapread:%d\n", i, map->readingHead); //temporaire
				map->start_dir = lineRead[i];
				return true;
			}
			if (lineRead[i] == 'S' || lineRead[i] == 'W' || lineRead[i] == 'E' || lineRead[i] == 'N')
				test++;
			i++;
		}
		free(lineRead);
		lineRead = readAndCleanLine(lineRead, map);
	}
	if (test > 1)
		return true;

	return false;
}

char *putReadingHeadInPlace(t_map *map)
{
	char *lineRead = NULL;

	map->LineOfEof = map->readingHead;
	close(map->fdMap);
	map->fdMap = open(map->filePath, O_RDONLY);
	map->readingHead = 0;

	lineRead = readAndCleanLine(lineRead, map);

	//on se remet a la bonne positions dans le fichier
	while (lineRead && map->readingHead < map->startMapInReading)
	{
		free(lineRead);
		lineRead = readAndCleanLine(lineRead, map);
	}
	return (lineRead);
}

// sub_function for parse map only in map file return in map->
void parseMap(t_map *map)
{
	int i;
	int j;
	j = 0;
	char *lineRead = NULL;

	//on cherche quand la map commence et la fin du fichier + check erreur sur la map
	if (checkMap(map))
		return ;
	lineRead = putReadingHeadInPlace(map);
	map->mapChar = malloc(sizeof(char *) * (map->LineOfEof - map->startMapInReading + 2));
	if (!map->mapChar)
		printf("TEMP malloc parseMap.c defaut\n");//temp

	//on imprime la map dans map.mapChar
	while (lineRead)
	{
		i = 0;
		while (lineRead[i])
			i++;
		map->mapChar[j] = malloc(sizeof(char) * (i + 2));
		i = 0;
		while (lineRead[i])
		{
			map->mapChar[j][i] = lineRead[i];
			i++;
		}
		map->mapChar[j][i] = '\0';
		free(lineRead);
		lineRead = readAndCleanLine(lineRead, map);
		j++;
	}
	map->mapChar[j] = NULL;
	free(lineRead);
}
