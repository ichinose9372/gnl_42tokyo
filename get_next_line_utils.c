/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:14:41 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/17 13:43:20 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	if ((char) c == 0)
		return ((char *)str + ft_strlen(str));
	while (*str != '\0')
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*p_s1;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	p_s1 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (p_s1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	char	*str_new;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(len + 1);
	if (str == 0)
		return (NULL);
	str_new = str;
	while (*s1 != 0)
	{
		*str = *s1;
		str++;
		s1++;
	}
	while (*s2 != 0)
	{
		*str = *s2;
		str++;
		s2++;
	}
	*str = '\0';
	return (str_new);
}
