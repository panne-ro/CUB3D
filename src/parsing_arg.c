/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panne-ro <panne-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:57 by panne-ro          #+#    #+#             */
/*   Updated: 2026/02/03 18:22:53 by panne-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//Take the number of args and the args to verify the number and the extension
//Return 0 if they are one arg and the extension is ".cub" else return 1 
int		parse(int argc, char **argv)
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
	return (0);
}

//Take a string to verify if the extansion is ".cub"
//Return 0 if is it or 1 if not
int		parse_extension(char *str)
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
		if (ft_strncmp(tmp, ".cub", ft_strlen(tmp)) == 0)
			return (0);
	}
	return (1);
}
