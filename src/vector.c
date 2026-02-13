/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:41:29 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 13:25:44 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_vector	*sum_vector(t_vector *vector1, t_vector *vector2)
{
	t_vector	*res;

	res = malloc(sizeof(t_vector));
	res->x = vector1->x + vector2->x;
	res->y = vector1->y + vector2->y;
	return (res);
}

t_vector	*sub_vector(t_vector *vector1, t_vector *vector2)
{
	t_vector	*res;

	res = malloc(sizeof(t_vector));
	res->x = vector1->x - vector2->x;
	res->y = vector1->y - vector2->y;
	return (res);
}

t_vector	*mul_vector(t_vector *vector, int scale)
{
	t_vector	*res;

	res = malloc(sizeof(t_vector));
	res->x = vector->x * scale;
	res->y = vector->y * scale;
	return (res);
}
