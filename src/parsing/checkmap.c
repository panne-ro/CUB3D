/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/03 18:23:38 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


// take a *t_map and init all the value at NULL or -1
void initMapStruct(t_map *map)
{
	int i;
	i = 0;

	map->fdMap = -1;

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

int checkmap(t_map *map)
{
	map->fdMap =  open(map->filePath, O_RDONLY);

	if (map->fdMap < 0)
	{
		printf("Error can't open map\n");
		return 0;
	}

	



}
