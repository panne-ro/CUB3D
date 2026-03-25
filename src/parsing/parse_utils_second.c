/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_second.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:30:18 by vboxuser          #+#    #+#             */
/*   Updated: 2026/03/25 14:31:03 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	sub_check_content_cc(char *tmp, t_map *map, int i, char *line_read)
{
	while (line_read[++i])
	{
		if (line_read[i] == 'C' && (line_read[i + 1] == ' '
				|| line_read[i + 1] == '\t'))
		{
			if (check_color_format(line_read))
			{
				map->valid_nbr_color = false;
				return (1);
			}
			i++;
			while (line_read[i] == ' ')
				i++;
			map->boolean = true;
			if (rgb_dispatch_info_file(line_read, tmp, i, map) == -2)
				map->valid_nbr_color = false;
			return (1);
		}
	}
	return (0);
}

int	sub_check_content_fc(char *tmp, t_map *map, int i, char *line_read)
{
	while (line_read[++i])
	{
		if (line_read[i] == 'F' && (line_read[i + 1] == ' '
				|| line_read[i + 1] == '\t'))
		{
			if (check_color_format(line_read))
			{
				map->valid_nbr_color = false;
				return (1);
			}
			i++;
			while (line_read[i] == ' ')
				i++;
			map->boolean = false;
			if (rgb_dispatch_info_file(line_read, tmp, i, map) == -2)
				map->valid_nbr_color = false;
			return (1);
		}
	}
}
