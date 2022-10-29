/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:19:48 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:21 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	struct_init(t_data *data)
{
	data->parsing.map = NULL;
	data->parsing.floor = NULL;
	data->parsing.ceiling = NULL;
	data->parsing.no_txt = NULL;
	data->parsing.so_txt = NULL;
	data->parsing.ea_txt = NULL;
	data->parsing.we_txt = NULL;
	data->parsing.player = 0;
	data->parsing.map_maxlen = 0;
	data->parsing.map_lines = 0;
	data->parsing.n_txt = 0;
	data->parsing.s_txt = 0;
	data->parsing.e_txt = 0;
	data->parsing.w_txt = 0;
	data->parsing.f = 0;
	data->parsing.c = 0;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Arg error"));
	struct_init(&data);
	if (!core_parsing(&data, argv))
		return (printf("Parsing error"));
	data.mlx_id = mlx_init();
	if (!textures_parsing(&data))
		return (printf("Textures error"));
	data.win_id = mlx_new_window(data.mlx_id, WIDTH, HEIGHT, "");
	data.img = mlx_new_image(data.mlx_id, WIDTH, HEIGHT);
	data.img2 = mlx_new_image(data.mlx_id, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.size_l, &data.e);
	data.addr2 = mlx_get_data_addr(data.img2, &data.bpp, &data.size_l, &data.e);
	draw_floor_ceiling(&data);
	mlx_put_image_to_window(data.mlx_id, data.win_id, data.img2, 0, 0);
	mlx_hook(data.win_id, 2, 0, ft_press, &data);
	mlx_hook(data.win_id, 3, 0, ft_release, &data);
	mlx_hook(data.win_id, 17, 0, safe_exit, &data);
	mlx_loop_hook(data.mlx_id, loop, &data);
	mlx_loop(data.mlx_id);
	return (1);
}
