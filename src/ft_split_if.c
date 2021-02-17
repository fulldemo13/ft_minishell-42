/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_if.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulldemo <fulldemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:11:50 by fulldemo          #+#    #+#             */
/*   Updated: 2021/02/13 12:32:43 by fulldemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count(const char *s, char c)
{
	t_div	div;

	ft_div_init(&div);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			ft_divisor_quotes(*s, &div);
			div.total++;
			while (*s)
			{
				s++;
				ft_divisor_quotes(*s, &div);
				if (*s == c && !div.f_double && !div.f_simple)
					break ;
			}
		}
	}
	return (div.total);
}

static char	*ft_malloc_word(const char *s, char c)
{
	char	*word;
	t_div	div;

	ft_div_init(&div);
	while (s[div.i])
	{
		ft_divisor_quotes(s[div.i], &div);
		if (s[div.i] == c && !div.f_double && !div.f_simple)
			break ;
		div.i++;
	}
	if (!(word = (char *)malloc(sizeof(char) * (div.i + 1))))
		return (NULL);
	div.i = 0;
	while (s[div.i])
	{
		ft_divisor_quotes(s[div.i], &div);
		if (s[div.i] == c && !div.f_double && !div.f_simple)
			break ;
		word[div.i] = s[div.i];
		div.i++;
	}
	word[div.i] = '\0';
	return (word);
}

char		**ft_malloc_tab(const char *s, char c)
{
	int		words;
	char	**tab;

	words = ft_count(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	return (tab);
}

char		**ft_split_if(const char *s, char c)
{
	char	**tab;
	t_div	div;

	tab = ft_malloc_tab(s, c);
	ft_div_init(&div);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			ft_divisor_quotes(*s, &div);
			tab[div.i] = ft_malloc_word(s, c);
			div.i++;
			while (*s)
			{
				s++;
				ft_divisor_quotes(*s, &div);
				if (*s == c && !div.f_double && !div.f_simple)
					break ;
			}
		}
	}
	tab[div.i] = NULL;
	return (tab);
}
