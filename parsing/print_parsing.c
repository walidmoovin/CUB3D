/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:35:26 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:13 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	verif_number_of_info(t_data *data)
{
	if (data->parsing.c != 1 || data->parsing.f != 1 || data->parsing.e_txt != 1
		|| data->parsing.n_txt != 1 || data->parsing.s_txt != 1
		|| data->parsing.w_txt != 1)
		return (0);
	return (1);
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
