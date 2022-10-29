/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:31:30 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/23 18:51:21 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
		*(char *)(s + i++) = 0;
}

void	*ft_calloc(int count, int size)
{
	void	*ret;

	ret = malloc(count * size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	while (s1[i] && ++i)
		ret[i - 1] = s1[i - 1];
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	free(s1);
	free(s2);
	return (ret);
}

char	*create_buffer(char *buffer, int *i)
{
	char	*ret;
	char	*p1;
	char	*p2;
	int		j;

	j = 0;
	p1 = ft_calloc(4096, sizeof(char));
	while (j < 4096)
	{
		p1[j++] = buffer[*i];
		if (buffer[*i] == '\0' || buffer[(*i)++] == '\n')
			return (p1);
	}
	p2 = create_buffer(buffer, i);
	ret = ft_strjoin(p1, p2);
	free(p1);
	free(p2);
	return (ret);
}

char	*get_next_line(int fd)
{
	static int	i;
	static char	buffer[513];
	char		*line;
	int			read_size;
	char		*ret;

	if (!*buffer)
		read_size = read(fd, buffer, 512);
	ret = ft_calloc(1, sizeof(char));
	while (buffer[i])
	{
		line = ft_strjoin(ret, create_buffer(buffer, &i));
		ret = line;
		if (buffer[i - 1] == '\n')
			break ;
		read_size = read(fd, buffer, 512);
		buffer[read_size] = 0;
		i = 0;
	}
	if (*ret)
		return (ret);
	free(ret);
	ft_bzero(buffer, 512);
	i = 0;
	return (NULL);
}
