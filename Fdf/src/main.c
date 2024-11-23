/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:26:57 by yousef            #+#    #+#             */
/*   Updated: 2024/11/23 02:15:12 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double Z_SCALE_FACTOR;

int handle_keypress(int keycode)
{
    if (keycode == ESC_KEY)
    {
        exit(0);
    }
    return (0);
}

int close_window()
{
    exit(0);
    return (0);
}

int main(int argc, char **argv)
{
    void *mlx;
    void *win;
    t_map *map;
    t_img img;

    if (argc != 2)
    {
        ft_putstr_fd("Usage: ./fdf <filename.fdf>\n", 1);
        return (1);
    }
	map = ft_read_file(argv[1]);
	double scale_x = (double)WINDOW_WIDTH / (map->width * 2);
	double scale_y = (double)WINDOW_HEIGHT / (map->height * 2);
	map->scale_factor = fmin(scale_x, scale_y);
	map->z_scale_factor = map->scale_factor * 0.1;
    mlx = mlx_init();
    if (!mlx)
        return (1);
    win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf - Wireframe Model");
    if (!win)
        return (1);
    img.img_ptr = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

    draw_map(map, &img);

    mlx_put_image_to_window(mlx, win, img.img_ptr, 0, 0);
    mlx_key_hook(win, handle_keypress, NULL);
    mlx_hook(win, 17, 0, close_window, NULL);
    mlx_loop(mlx);
    return (0);
}

