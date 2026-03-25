/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboxuser <vboxuser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:21:25 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/25 14:30:59 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// a sub_functions for find NO in files and
// returns texture of north (NO ./holakalainorth.texture)
char	*check_content_no(t_map *map, char *tmp, int i)
{
	char	*line_read;

	line_read = NULL;
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
		i = -1;
		while (line_read[++i])
		{
			if (line_read[i] == 'N' && line_read[i + 1]
				&& line_read[i + 1] == 'O')
			{
				i = i + 2;
				if (!line_read[i])
					return (NULL);
				while (line_read[i] && line_read[i] == ' ')
					i++;
				return (copy_content(line_read, tmp, i));
			}
		}
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
	free(line_read);
	return (NULL);
}

// a sub_functions for find SO in files and returns
// texture of south (NO ./ilovepdfsouth.texture)
char	*check_content_so(t_map *map, char *tmp, int i)
{
	char	*line_read;

	line_read = NULL;
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
		i = -1;
		while (line_read[++i])
		{
			if (line_read[i] == 'S' && line_read[i + 1]
				&& line_read[i + 1] == 'O')
			{
				i = i + 2;
				if (!line_read[i])
					return (NULL);
				while (line_read[i] && line_read[i] == ' ')
					i++;
				return (copy_content(line_read, tmp, i));
			}
		}
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
	free(line_read);
	return (NULL);
}

// a sub_functions for find WE in files and returns
// texture of west (WE ./westside.2pac.bigi...texture)
char	*check_content_we(t_map *map, char *tmp, int i)
{
	char	*line_read;

	line_read = NULL;
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
		i = -1;
		while (line_read[++i])
		{
			if (line_read[i] == 'W' && line_read[i + 1]
				&& line_read[i + 1] == 'E')
			{
				i = i + 2;
				if (!line_read[i])
					return (NULL);
				while (line_read[i] && line_read[i] == ' ')
					i++;
				return (copy_content(line_read, tmp, i));
			}
		}
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
	free(line_read);
	return (NULL);
}

// a sub_functions for find EA in files and returns
// texture of east (EA ./bigchybreeastcost.texture)
char	*check_content_ea(t_map *map, char *tmp, int i)
{
	char	*line_read;

	line_read = NULL;
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
		i = -1;
		while (line_read[++i])
		{
			if (line_read[i] == 'E' && line_read[i + 1]
				&& line_read[i + 1] == 'A')
			{
				i = i + 2;
				if (!line_read[i])
					return (NULL);
				while (line_read[i] && line_read[i] == ' ')
					i++;
				return (copy_content(line_read, tmp, i));
			}
		}
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
	free(line_read);
	return (NULL);
}

//sub fonction of check_content_master
//resturn all of rgb in array of t_map for the floor
//faut faire bellek ya pas les erreurs d'over-nombre pour l'instant
//(F 0,250,300,54654,484,31,5156,4,51,48,4,3,84,5)
void	check_content_fc(char *tmp, t_map *map, int i, char *line_read)
{
	line_read = read_and_clean_line(line_read, map);
	while (line_read)
	{
		i = -1;
		if (sub_check_content_fc(tmp, map, i, line_read))
		{
			free(line_read);
			return ;
		}
		free(line_read);
		line_read = read_and_clean_line(line_read, map);
	}
}
