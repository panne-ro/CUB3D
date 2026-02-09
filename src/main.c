/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/09 23:41:32 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void freeMap(t_map *map)
{
	int i = 0;
	// free(map->floorColor);
	// free(map->ceilingColor);
	free(map->eastTexture);
	free(map->westTexture);
	free(map->northTexture);
	free(map->southTexture);

	while (map->mapChar[i])
	{
		free(map->mapChar[i]);
		i++;
	}
	free(map->mapChar);
	// free(map->filePath);

	// free(map->fdMap);
	// free(map->floorColor);
	// free(map->startMapInReading);
	// free(map->heightOfMap);
	// free(map->LineOfEof);
}

int main(int argc, char **argv)
{
	if (checkArg(argc, argv) == 1)
		return (1);
	printf("%s\n", argv[1]);

	t_map *map;
	map = malloc(sizeof(t_map));

	initMapStruct(map, argv[1]);

	// int fd = open(argv[1], O_RDONLY);
	// char *mdr = get_next_line(fd);
	// printf("%s\n", mdr);
	// free(mdr);
	freeMap(map);
	free(map);
	return (0);
}
