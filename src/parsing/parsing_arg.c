/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:57 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/13 17:21:50 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//Take the number of args and the args to verify the number and the extension
//Return 0 if they are one arg and the extension is ".cub" else return 1
int		checkArg(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nMap is required\n");
		return (1);
	}
	if (extensionCheck(argv[1]))
	{
		printf("Error\nMap extension is not a \".cub\"\n");
		return (1);
	}
	return (0);
}

//Take a string to verify if the extansion is ".cub"
//Return 0 if is it or 1 if not
int		extensionCheck(char *str)
{
	int		i;
	int		j;
	char	tmp[7000];

	i = 0;
	j = 0;
	while(str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		while(str[i])
		{
			tmp[j] = str[i];
			i++;
			j++;
		}
		tmp[j] = '\0';
		if (ft_strncmp(tmp, ".cub", ft_strlen(tmp)) == 0 && ft_strncmp(tmp, ".cub", ft_strlen(str)) == 0)
			return (0);
	}
	return (1);
}
