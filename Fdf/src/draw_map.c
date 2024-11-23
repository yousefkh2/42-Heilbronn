/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:19:55 by yousef            #+#    #+#             */
/*   Updated: 2024/11/23 02:18:00 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "fdf.h"

void ft_iso_projection(double *x, double *y, double z)
{
    double previous_x = *x;
    double previous_y = *y;
    double angle = 0.523599; // Approximately 30 degrees
    
    *x = (previous_x - previous_y) * cos(angle);
    *y = (previous_x + previous_y) * sin(angle) - z;
}


void draw_map(t_map *map, t_img *img)
{
    int x;
    int y;

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

void draw_lines(t_map *map, int x, int y, t_img *img)
{
    t_point p0;
    t_point p1;

    if (x < map->width - 1)
    {
        p0 = ft_get_point(x, y, map);
        p1 = ft_get_point(x + 1, y, map);
        ft_draw_line(p0, p1, img);
    }
    if (y < map->height - 1)
    {
        p0 = ft_get_point(x, y, map);
        p1 = ft_get_point(x, y + 1, map);
        ft_draw_line(p0, p1, img);
    }
}


t_point ft_get_point(int x, int y, t_map *map)
{
	t_point point;

	point.x = x;
	point.y = y;
	point.z = map->array[y][x];
	// Apply scaling if necessary
    point.x *= map->scale_factor;
    point.y *= map->scale_factor;
    point.z *= map->z_scale_factor;
    // Apply isometric projection
    ft_iso_projection(&point.x, &point.y, point.z);
	printf("Point (%d, %d): x = %f, y = %f, z = %f\n", x, y, point.x, point.y, point.z);
    return point;
}

void ft_draw_line(t_point p0, t_point p1, t_img *img)
{
    double x = p0.x;
    double y = p0.y;
    double dx = p1.x - p0.x;
    double dy = p1.y - p0.y;
    double steps = fmax(fabs(dx), fabs(dy));
    double x_inc = dx / steps;
    double y_inc = dy / steps;
    int i = 0;

	printf("Drawing line from (%f, %f) to (%f, %f), steps = %f\n", p0.x, p0.y, p1.x, p1.y, steps);

    while (i <= steps)
    {
        put_pixel_to_img(img, x + X_OFFSET, y + Y_OFFSET, 0xFFFFFF);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

