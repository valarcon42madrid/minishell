/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:53:22 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/18 12:53:24 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_ltrim(char const *s1, char c)
{
	char	*sp;

	sp = (char *)s1;
	while (*sp == c && *sp)
		sp++;
	if (!*sp)
		return ((char *)s1);
	return (sp);
}

static char	*ft_rtrim(char const *s1, char c)
{
	char	*sp;

	sp = (char *)(s1 + ft_strlen(s1) - 1);
	while (*sp == c && (sp != s1))
		sp--;
	return ((char *)sp);
}

char	*ft_strtrimc(char const *s1, char c)
{
	char	*dst;
	char	*lt;
	char	*rt;
	int		cont;

	if (s1 == (void *)0)
		return (0);
	if (!ft_strncmp(s1, "", 1))
		return ((char *)s1);
	cont = 0;
	lt = ft_ltrim(s1, c);
	rt = ft_rtrim(s1, c);
	if (lt == rt)
		return (ft_strdup(""));
	while (&lt[cont] != rt)
		cont++;
	dst = malloc(sizeof(char) * (cont + 2));
	if (!dst)
		return (0);
	ft_strlcpy(dst, lt, cont + 2);
	return (dst);
}
