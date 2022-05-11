/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:35:26 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 13:36:45 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_all(t_data *data, char **file)
{
	print_file(file);
	print_map(data);
	print_txt_colors(data);
}

void	print_file(char **file)
{
	int	i;

	i = -1;
	printf("-----FILE-----\n");
	while (file[++i])
		printf("%s", file[i]);
}

void	print_map(t_data *data)
{
	int	i;

	i = -1;
	printf("-----MAP-----\n");
	while (data->parsing.map[++i])
		printf("%s", data->parsing.map[i]);
}

void	print_txt_colors(t_data *data)
{
	int	i;

	i = -1;
	printf("-----FLOOR-----\n");
	while (data->parsing.floor[++i])
		printf("%s\n", data->parsing.floor[i]);
	i = -1;
	printf("-----CEILING-----\n");
	while (data->parsing.ceiling[++i])
		printf("%s\n", data->parsing.ceiling[i]);
	printf("-----TXT-----\n");
	printf("%s", data->parsing.no_txt);
	printf("%s", data->parsing.so_txt);
	printf("%s", data->parsing.ea_txt);
	printf("%s", data->parsing.we_txt);
}

int	ft_isdigit(char c)
{
	if ((c < '0' || c > '9') && c != '\n')
		return (0);
	return (1);
}
