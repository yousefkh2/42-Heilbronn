/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:30:32 by ykhattab          #+#    #+#             */
/*   Updated: 2024/11/28 19:48:53 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

// Define window dimensions and constants
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define DEFAULT_COLOR 0xFFFFFF
// #define SCALE_FACTOR 20
// #define Z_SCALE_FACTOR 1
# define X_OFFSET 400
# define Y_OFFSET 300

// Define ESC key code (adjust based on your system)
# define ESC_KEY 53 // MacOS
// #define ESC_KEY 65307 // Linux (X11)

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
	double	scale_factor;
	double	z_scale_factor;
}			t_map;

typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_l;
	int		endian;
}			t_img;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	*map;
}			t_vars;

// Function prototypes
t_map		*ft_map_init(void);
t_map		*ft_read_file(const char *filename);
int			ft_atoi_base(const char *str, int base);
void		setup_mlx(t_vars *vars);
int			ft_get_width(const char *line);
int			ft_get_height(const char *filename);
void		ft_fill_row(t_point *row, char *line, t_map *map);
int			render(void *param);
void		initialize_vars(t_vars *vars, char *filename);
void		ft_iso_projection(double *x, double *y, double z);
t_point		ft_process_point(int x, int y, t_map *map);
void		ft_draw_line(t_point p0, t_point p1, t_img *img);
void		draw_lines(t_map *map, int x, int y, t_img *img);
void		draw_map(t_map *map, t_img *img);
void		read_map_data(int fd, t_map *map);
t_map		*initialize_map_and_width(int fd);
int			open_file(const char *filename);
void		put_pixel_to_img(t_img *img, int x, int y, int color);

int			handle_keypress(int keycode, t_vars *vars);
int			close_window(t_vars *vars);
void		free_map(t_map *map);
void		cleanup_mlx(t_vars *vars);

#endif