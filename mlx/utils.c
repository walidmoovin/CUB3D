/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:20 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 13:35:57 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = data->addr + (y * data->size_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = data->addr2 + (y * data->size_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	safe_exit(t_data *data)
{
	mlx_destroy_window(data->mlx_id, data->win_id);
	exit(0);
	return (1);
}
