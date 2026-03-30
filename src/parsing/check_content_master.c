/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_master.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:26:50 by panne-ro          #+#    #+#             */
/*   Updated: 2026/03/30 14:33:54 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	process_token(t_map *map, char *line_read, char tmp[1000], int i)
{
	int	token_nbr;

	token_nbr = return_of_the_token(map, line_read);
	if (token_nbr == 1)
		map->northTexture = check_content_no(map, tmp, i, line_read);
	else if (token_nbr == 2)
		map->southTexture = check_content_so(map, tmp, i, line_read);
	else if (token_nbr == 3)
		map->westTexture = check_content_we(map, tmp, i, line_read);
	else if (token_nbr == 4)
		map->eastTexture = check_content_ea(map, tmp, i, line_read);
	else if (token_nbr == 5)
	{
		map->fc_taken = true;
		map->is_cc = false;
		map->is_fc = true;
		check_content_fc(tmp, map, i, line_read);
	}
	else if (token_nbr == 6)
	{
		map->is_cc = true;
		map->is_fc = false;
		map->cc_taken = true;
		check_content_cc(tmp, map, i, line_read);
	}
}

int	check_content_master(t_map *map)
{
	char	*line_read;
	char	tmp[1000];
	int		i;

	line_read = NULL;
	i = -1;
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
		process_token(map, line_read, tmp, i);
		free(line_read);
		if (map->northTexture && map->southTexture && map->westTexture
			&& map->eastTexture && map->fc_taken && map->cc_taken)
			break ;
		line_read = read_and_clean_line(line_read, map);
	}
	parse_map(map);
	return (0);
}

//final check of mapChar for t_map *map
bool	verif_map(t_map *map, int i, int nbr_player)
{
	int	j;
	int	y;
	int	x;

	if (!map->mapChar)
		return (true);
	if (sub_loop_master_in_verif_map(map, &i, &j, &nbr_player) == true)
		return (true);
	if (nbr_player > 1 || !nbr_player)
		return (true);
	if (ext_is_all_wall(map) == 0)
		return (true);
	if (!map->copy_map)
		map->copy_map = copy_map(map->mapChar);
	x = map->player_x;
	y = map->player_y;
	flood_fill(x, y, map);
	if (map->isClosed == false)
		return (true);
	return (false);
}
