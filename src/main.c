/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/05 19:08:26 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int main(int argc, char **argv)
{
	if (checkArg(argc, argv) == 1)
		return (1);
	printf("%s\n", argv[1]);

	t_map *map;
	map = malloc(sizeof(t_map));

	initMapStruct(map, argv[1]);

	checkmap(map);

	return (0);
}
