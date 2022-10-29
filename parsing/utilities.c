/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:20:50 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:15 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	str_cut(char *str, int begin, int len)
{
	int	l;

	l = ft_strlen(str);
	if (len < 0)
		len = l - begin;
	if (begin + len > l)
		len = l - begin;
	ft_memmove(str + begin, str + begin + len, l - len + 1);
	return (len);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dstc;
	char	*srcc;

	dstc = (char *)dst;
	srcc = (char *)src;
	if (dstc == srcc)
		return (dst);
	if (srcc < dstc)
	{
		while (len-- != 0)
			*(dstc + len) = *(srcc + len);
		return (dst);
	}
	while (len-- != 0)
		*dstc++ = *srcc++;
	return (dst);
}

int	ft_atoi(char *str)
{
	int	atoi;
	int	sign;
	int	i;

	sign = 1;
	atoi = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi = (atoi * 10) + (str[i] - '0');
		i++;
	}
	return (atoi * sign);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*str;
	int		len;

	if (!*src)
	{
		str = malloc(sizeof(char));
		*str = '\0';
		return (str);
	}
	len = ft_strlen(src);
	str = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
