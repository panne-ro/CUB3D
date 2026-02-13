/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:05:20 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/09 15:50:24 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int main(void)
{
	char **test = malloc(sizeof(char *) * (10 + 1));
	if (!test)
		return (1);

	for (size_t i = 0; i < 10; i++)
	{
		test[i] = malloc(sizeof(char) * (10 + 1));
		if (!test[i])
			return (1);
		for (size_t f = 0; f < 10; f++)
			test[i][f] = '0';
		test[i][10] = '\0';
	}
	test[10] = NULL;

	for (size_t i = 0; i < 10; i++)
		printf("%s\n", test[i]);

	/* initialize graphics */
	init(test);

	for (size_t i = 0; i < 10; i++)
		free(test[i]);
	free(test);

	return (0);
}
