/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleschev <mleschev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:30:47 by mleschev          #+#    #+#             */
/*   Updated: 2026/03/05 11:19:36 by mleschev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*array;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	array = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	while (i < s1_len)
	{
		array[i] = s1[i];
		i++;
	}
	while (j < s2_len)
	{
		array[i + j] = s2[j];
		j++;
	}
	array[i + j] = '\0';
	return (array);
}
