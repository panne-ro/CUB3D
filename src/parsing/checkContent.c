/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkContent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:21:25 by mleschev          #+#    #+#             */
/*   Updated: 2026/02/04 00:21:52 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3D.h"

// a sub_functions for find NO in files and returns texture of north (NO ./holakalainorth.texture)
char *checkContentNO(int fd, char *tmp, char *lineRead)
{
	int i;

	if (!lineRead)
		return NULL;
	while (lineRead)
	{
		i = 0;
		while (lineRead[i])
		{
			if (lineRead[i] == 'N' && lineRead[i + 1] && lineRead[i + 1] == 'O')
			{
				i = i + 2;
				if (!lineRead[i])
					return NULL;
				while (lineRead[i] && lineRead[i] == ' ')
					i++;
				return copyContent(lineRead, tmp, i);
			}
			i++;
		}
		lineRead = get_next_line(fd);
	}
	return NULL;
}

// a sub_functions for find SO in files and returns texture of south (NO ./ilovepdfsouth.texture)
char *checkContentSO(int fd, char *tmp, char *lineRead)
{
	int i;

	if (!lineRead)
		return NULL;
	while (lineRead)
	{
		i = 0;
		while (lineRead[i])
		{
			if (lineRead[i] == 'S' && lineRead[i + 1] && lineRead[i + 1] == 'O')
			{
				i = i + 2;
				if (!lineRead[i])
					return NULL;
				while (lineRead[i] && lineRead[i] == ' ')
					i++;
				return copyContent(lineRead, tmp, i);
			}
			i++;
		}
		lineRead = get_next_line(fd);
	}
	return NULL;
}

// a sub_functions for find WE in files and returns texture of west (WE ./westside.2pac.bigi...texture)
char *checkContentWE(int fd, char *tmp, char *lineRead)
{
	int i;

	if (!lineRead)
		return NULL;
	while (lineRead)
	{
		i = 0;
		while (lineRead[i])
		{
			if (lineRead[i] == 'W' && lineRead[i + 1] && lineRead[i + 1] == 'E')
			{
				i = i + 2;
				if (!lineRead[i])
					return NULL;
				while (lineRead[i] && lineRead[i] == ' ')
					i++;
				return copyContent(lineRead, tmp, i);
			}
			i++;
		}
		lineRead = get_next_line(fd);
	}
	return NULL;
}

// a sub_functions for find EA in files and returns texture of east (EA ./bigchybreeastcost.texture)
char *checkContentEA(int fd, char *tmp, char *lineRead)
{
	int i;

	if (!lineRead)
		return NULL;
	while (lineRead)
	{
		i = 0;
		while (lineRead[i])
		{
			if (lineRead[i] == 'E' && lineRead[i + 1] && lineRead[i + 1] == 'A')
			{
				i = i + 2;
				if (!lineRead[i])
					return NULL;
				while (lineRead[i] && lineRead[i] == ' ')
					i++;
				return copyContent(lineRead, tmp, i);
			}
			i++;
		}
		lineRead = get_next_line(fd);
	}
	return NULL;
}
//sub fonction of checkcontentmaster resturn all of rgb in array of t_map for the floor 
void checkContentFC(int fd, char *tmp, char *lineRead, t_map *map)
{ //faut faire bellek ya pas les erreurs d'over-nombre pour l'instant (F 0,250,300,54654,484,31,5156,4,51,48,4,3,84,5)
	int i;

	if (!lineRead)
		return ;
	while (lineRead)
	{
		i = 0;
		while (lineRead[i])
		{
			if (lineRead[i] == 'F')
			{
				i++;
				if (!lineRead[i])
					return ;
				while (lineRead[i] && lineRead[i] == ' ')
					i++;
				rgbDispatchInfoFile(lineRead, tmp, i, map);
                return ;
			}
			i++;
		}
		lineRead = get_next_line(fd);
	}
}

// a sub_functions for CheckContent_XXXX, copy a string in file at lineread[i] to tmp and return it (to free)
char *copyContent(char *lineRead, char *tmp, int i)
{
	int j;
    char *result;
	j = 0;
	while (lineRead[i] && lineRead[i] != '\n')
	{
		tmp[j] = lineRead[i];
		j++;
		i++;
	}
	tmp[j] = 0;
    result = malloc(sizeof(char) * (j + 1));
    ft_strlcpy(result, tmp, j + 1);
	return result;
}
// sub fonction for dispatch rgb (floor or ceiling) into t_map data
void rgbDispatchInfoFile(char *lineRead, char *tmp, int i, t_map *map)
{
    int j;
    int nbr;

    nbr = 0;

    while (lineRead[i] && lineRead[i] != '\n' && nbr < 3)
    {
        j = 0;
        while (lineRead[i] && lineRead[i] != '\n' && lineRead[i] != ',')
        {
            tmp[j] = lineRead[i];
            j++;
            i++;
        }
        tmp[j] = 0;
        map->floorColor[nbr] = ft_atoi(tmp);
        i++;
        nbr++;
    }
}

