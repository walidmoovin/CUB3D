/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:23:11 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 11:28:45 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*create_line(int fd, char *parts)
{
	char	*line;
	int		rd_ret;

	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line)
		return (NULL);
	rd_ret = 1;
	while (!ft_strchr(parts, '\n') && rd_ret)
	{
		rd_ret = read(fd, line, BUFFER_SIZE);
		if (rd_ret == -1)
		{
			free(line);
			return (NULL);
		}
		line[rd_ret] = '\0';
		parts = ft_strjoin(parts, line);
	}
	free(line);
	return (parts);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*parts;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	parts = create_line(fd, parts);
	if (!parts)
		return (NULL);
	line = fill_line(parts);
	parts = new_parts(parts);
	return (line);
}
