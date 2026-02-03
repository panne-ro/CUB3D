/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/03 18:08:18 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nJust map required\n");
		return (1);		
	}
	if (parse_extension(argv[1]) == 1)
	{
		printf("Error\nMap extension is \".cub\"\n");
		return (1);
	}
	printf("%s", argv[1]);
	return (0);
}