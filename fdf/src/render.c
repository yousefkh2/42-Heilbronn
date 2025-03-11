/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:19:55 by yousef            #+#    #+#             */
/*   Updated: 2024/11/28 18:58:44 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_map *map, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			draw_lines(map, x, y, img);
			x++;
		}
		y++;
	}
}

void	draw_lines(t_map *map, int x, int y, t_img *img)
{
	t_point	p0;
	t_point	p1;

	if (x < map->width - 1)
	{
		p0 = ft_process_point(x, y, map);
		p1 = ft_process_point(x + 1, y, map);
		ft_draw_line(p0, p1, img);
	}
	if (y < map->height - 1)
	{
		p0 = ft_process_point(x, y, map);
		p1 = ft_process_point(x, y + 1, map);
		ft_draw_line(p0, p1, img);
	}
}

t_point	ft_process_point(int x, int y, t_map *map)
{
	t_point	point;

	point = map->points[y][x];
	point.x = x - (map->width / 2.0);
	point.y = y - (map->height / 2.0);
	point.x *= map->scale_factor;
	point.y *= map->scale_factor;
	point.z *= map->z_scale_factor;
	ft_iso_projection(&point.x, &point.y, point.z);
	point.x += X_OFFSET;
	point.y += Y_OFFSET;
	return (point);
}

void	ft_draw_line(t_point p0, t_point p1, t_img *img)
{
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;
	double	ratio;

	steps = fmax(fabs(p1.x - p0.x), fabs(p1.y - p0.y));
	x_inc = 0;
	y_inc = 0;
	i = 0;
	if (steps == 0)
	{
		put_pixel_to_img(img, (int)p0.x, (int)p0.y, 0xFFFFFF);
		return ;
	}
	x_inc = (p1.x - p0.x) / steps;
	y_inc = (p1.y - p0.y) / steps;
	while (i <= steps)
	{
		ratio = i / steps;
		put_pixel_to_img(img, (int)p0.x, (int)p0.y, p0.color);
		p0.x += x_inc;
		p0.y += y_inc;
		i++;
	}
}

void	ft_iso_projection(double *x, double *y, double z)
{
	double	previous_x;
	double	previous_y;
	double	angle;

	previous_x = *x;
	previous_y = *y;
	angle = 0.523599;
	*x = (previous_x - previous_y) * cos(angle);
	*y = (previous_x + previous_y) * sin(angle) - z;
}
