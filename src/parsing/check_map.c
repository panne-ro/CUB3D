/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 18:02:13 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/30 13:29:14 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// take a *t_map, the path for map and init all the value at NULL
//or -1 and pass into checkmap()
void	init_map_struct(t_game **gameAddr, char *pathToMap)
{
	int		i;
	t_game	*game;

	game = *gameAddr;
	i = 0;
	game->map->filePath = pathToMap;
	game->map->fdMap = -1;
	game->map->mapChar = NULL;
	game->map->readingHead = 0;
	while (i < 3)
	{
		game->map->ceilingColor[i] = -1;
		game->map->floorColor[i] = -1;
		i++;
	}
	game->map->eastTexture = NULL;
	game->map->westTexture = NULL;
	game->map->northTexture = NULL;
	game->map->southTexture = NULL;
	game->map->startMapInReading = 0;
	game->map->LineOfEof = 0;
	game->map->valid_nbr_color = true;
	game->map->isValid = false;
	game->map->isClosed = false;
	checkmap(gameAddr);
}

// take a t_map already init with init_map_struct() and check all the infos
//inside return an error with printf and -1 or 0 if all good
int	checkmap(t_game **gameAddr)
{
	t_game	*game;

	game = *gameAddr;
	game->map->fdMap = open(game->map->filePath, O_RDONLY);
	if (game->map->fdMap < 0)
		close_all(gameAddr, "can't open map");
	if (check_double_master(game->map))
		close_all(gameAddr, "doublon file detected");
	check_content_master(game->map);
	return (0);
}

int	return_of_the_value(char *line_read, int i)
{
	if (line_read[i] && line_read[i] == 'N' && line_read[i + 1]
		&& line_read[i + 1] == 'O')
		return (1);
	else if (line_read[i] && line_read[i] == 'S' && line_read[i + 1]
		&& line_read[i + 1] == 'O')
		return (2);
	else if (line_read[i] && line_read[i] == 'W' && line_read[i + 1]
		&& line_read[i + 1] == 'E')
		return (3);
	else if (line_read[i] && line_read[i] == 'E' && line_read[i + 1]
		&& line_read[i + 1] == 'A')
		return (4);
	else if (line_read[i] && line_read[i] == 'F' && line_read[i + 1]
		&& line_read[i + 1] == ' ')
		return (5);
	else if (line_read[i] && line_read[i] == 'C' && line_read[i + 1]
		&& line_read[i + 1] == ' ')
		return (6);
	return (0);
}

int	return_of_the_token(t_map *map, char	*line_read)
{
	int	i;
	int		value_return;
	i = 0;
	value_return = 0;

	while (line_read[i])
	{
		value_return = return_of_the_value(line_read, i);
		if (value_return)
			return (value_return);
		i++;
	}
	return (0);
}

int	check_content_master(t_map *map)
{
	char	*line_read;
	char	tmp[1000];
	int		i;
	int		token_nbr = 0;

	line_read = NULL;
	i = -1;
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
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
			printf("aled 1 %s\n", line_read);
			check_content_fc(tmp, map, i, line_read);
		}
		else if (token_nbr == 6)
		{
			map->is_cc = true;
			map->is_fc = false;
			map->cc_taken = true;
			printf("aled 2 %s\n", line_read);
			check_content_cc(tmp, map, i, line_read);
		}
		printf("aled : %d\n",token_nbr);
		printf("no : %s\n",map->northTexture);
		printf("so : %s\n",map->southTexture);
		printf("we : %s\n",map->westTexture);
		printf("ea : %s\n",map->eastTexture);

		printf("fc : %ld",map->floorColor[0]);
		printf(",%ld",map->floorColor[1]);
		printf(",%ld\n",map->floorColor[2]);

		printf("cc : %ld",map->ceilingColor[0]);
		printf(",%ld",map->ceilingColor[1]);
		printf(",%ld\n",map->ceilingColor[2]);

		printf("readinghead : %d\n\n", map->readingHead);
		free(line_read);
		if (map->northTexture && map->southTexture && map->westTexture && map->eastTexture && map->fc_taken && map->cc_taken)
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

	printf("DB1\n");
	if (!map->mapChar)
		return (true);
	printf("DB1\n");
	if (sub_loop_master_in_verif_map(map, &i, &j, &nbr_player) == true)
		return (true);
	printf("DB1\n");

	if (nbr_player > 1 || !nbr_player)
		return (true);
	printf("DB1\n");

	if (ext_is_all_wall(map) == 0)
		return (true);
	printf("DB1\n");

	if (!map->copy_map)
		map->copy_map = copy_map(map->mapChar);
	x = map->player_x;
	y = map->player_y;
	flood_fill(x, y, map);
	if (map->isClosed == false)
		return (true);
	return (false);
}
