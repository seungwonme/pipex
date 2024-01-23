/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anseungwon <anseungwon@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:19:23 by seunan            #+#    #+#             */
/*   Updated: 2023/07/01 16:00:10 by anseungwon       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**str_free(char **out, int arridx)
{
	int	i;

	i = 0;
	while (i <= arridx)
	{
		free(out[i]);
		++i;
	}
	free(out);
	return (NULL);
}

static int	get_cnt(char const *s, char c)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && ((s[i + 1] == c) || s[i + 1] == '\0'))
			++cnt;
		++i;
	}
	return (cnt);
}

static char	*str_maker(const char *s, int *sidx, char c, char suffix)
{
	char	*str;
	int		strlen;

	strlen = 0;
	while (s[*sidx] == c)
		++*sidx;
	while (s[*sidx] != '\0' && s[*sidx] != c)
	{
		++strlen;
		++*sidx;
	}
	str = (char *) ft_calloc(sizeof(char), (strlen + 1 + (suffix != '\0')));
	if (!str)
		return (NULL);
	*sidx -= strlen;
	strlen = 0;
	while (s[*sidx] != '\0' && s[*sidx] != c)
	{
		str[strlen] = s[*sidx];
		++*sidx;
		++strlen;
	}
	str[strlen] = suffix;
	return (str);
}

char	**ft_split(char const *s, char c, char suffix)
{
	char	**out;
	char	*str;
	int		sidx;
	int		cnt;
	int		i;

	cnt = get_cnt(s, c);
	out = (char **)ft_calloc(sizeof(char *), (cnt + 1));
	if (!out)
		return (NULL);
	sidx = 0;
	i = 0;
	while (i < cnt)
	{
		str = str_maker(s, &sidx, c, suffix);
		if (!str)
			return (str_free(out, i));
		out[i] = str;
		++i;
	}
	return (out);
}
