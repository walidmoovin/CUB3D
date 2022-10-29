/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:23:01 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/23 19:00:14 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 43
# endif

# define WIDTH 600
# define HEIGHT 400
# define KEY_ECHAP 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_SHIFT 257
# define KEY_CTRL 256
# define ROTATE_LEFT 123
# define ROTATE_RIGHT 124
# define TEX_WIDTH 500
# define TEX_HEIGHT	500

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

typedef struct s_parsing
{
	char	**map;
	char	**floor;
	char	**ceiling;
	char	*no_txt;
	char	*so_txt;
	char	*we_txt;
	char	*ea_txt;
	int		player;
	int		map_lines;
	int		map_maxlen;
	int		n_txt;
	int		s_txt;
	int		w_txt;
	int		e_txt;
	int		f;
	int		c;
}	t_parsing;

typedef struct s_key
{
	int		w;
	int		s;
	int		d;
	int		a;
	int		rot_left;
	int		rot_right;
	int		shift;
	int		ctrl;
}	t_key;

typedef struct s_raycasting
{
	double	player_posx;
	double	player_posy;
	double	player_dirx;
	double	player_diry;
	double	planex;
	double	planey;
	int		x;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		color;
	int		texx;
	int		texy;
	double	texpos;
}	t_rayc;

typedef struct s_text
{
	int	*add1;
	int	*add2;
	int	*add3;
	int	*add4;
}	t_text;

typedef struct s_data
{
	void		*mlx_id;
	void		*win_id;
	void		*img;
	void		*img2;
	char		*addr;
	char		*addr2;
	int			bpp;
	int			size_l;
	int			e;
	int			**map;
	t_key		keys;
	t_rayc		rayc;
	t_parsing	parsing;
	t_text		text;
}	t_data;

/*
** ----- gnl -----
*/
int		number_of_tables(char **str);
int		ft_strlen(char *s);
char	*get_next_line(int fd);
int		ft_strchr(char *s, char c);
char	*ft_strjoin(char *parts, char *line);
/*
** ----- ft_split.c -----
*/
char	**ft_split(char *str, char separator);
int		only_sp(char *str);
/*
** ----- utilities.c -----
*/
int		str_cut(char *str, int begin, int len);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_atoi(char *str);
char	*ft_strdup(char *src);
int		ft_strcmp(char *s1, char *s2);
/*
** ----- parsing_utilities.c -----
*/
int		txt_linec(char *str, char first, char second);
int		map_char(char c);
int		map_line(char *str);
int		txt_line(char *str, char first, char second);
char	*get_txt(char *str, t_data *data);
char	**get_color(char **str, t_data *data);
int		free_return(char **tab, char **tab2);
int		verif_number_of_info(t_data *data);
/*
** ----- parsing_utilities2.c -----
*/
int		file_lines(char *str);
void	map_info(char **file, t_data *data);
int		valid_colors(t_data *data);
void	player_dir(char dir, t_data *data);
/*
** ----- parsing.c -----
*/
void	free_tab(char **tab);
int		core_parsing(t_data *data, char **argv);
char	**parse_file(char *argv);
void	parse_map(char **str, t_data *data);
void	parse_txt(char **str, t_data *data);
int		verif_lot_map(char **str);
int		verif_color_utils(t_data *data);
/*
** ----- fileverif.c -----
*/
int		fileverif(char *str);
int		fileverif2(char **str);
int		verifmap(t_data *data);
int		is_direction(char c);
/*
** ----- print_parsing.c -----
*/
void	print_all(t_data *data, char **file);
void	print_file(char **file);
void	print_txt_colors(t_data *data);
void	print_map(t_data *data);
int		ft_isdigit(char c);
/*
** ----- mlx_utils.c -----
*/
int		loop(t_data *data);
void	draw_floor_ceiling(t_data *data);
int		creatergb(int r, int g, int b);
int		textures_parsing(t_data *data);
void	*get_addr(char *text, t_data *data);
int		wall_algo(t_data *data, int x, int y);
/*
** ----- mlx.c -----
*/
void	*ft_calloc(int count, int size);
void	raycasting(t_data *data);
void	init(t_data *data);
void	dda(t_data *data);
void	step_init(t_data *data);
void	draw_textures(t_data *data);
/*
** ----- movements.c -----
*/
int		ft_press(int keycode, t_data *data);
int		ft_release(int keycode, t_data *data);
void	keys_loop(t_data *data);
void	strafe(t_data *data);
void	move(t_data *data);
/*
** ----- utils.c -----
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color);
int		safe_exit(t_data *data);
void	init_datas(t_data *data);
#endif