/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 23:26:57 by yousef            #+#    #+#             */
/*   Updated: 2024/11/28 20:09:26 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	size_t	len;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <filename.fdf>\n", 1);
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".fdf", 4) != 0)
	{
		ft_putstr_fd("Error: The file must have a .fdf extension.\n", 1);
		return (1);
	}
	initialize_vars(&vars, argv[1]);
	setup_mlx(&vars);
	mlx_loop(vars.mlx);
	free_map(vars.map);
	cleanup_mlx(&vars);
	return (0);
}

void	initialize_vars(t_vars *vars, char *filename)
{
	double	scale_x;
	double	scale_y;

	vars->map = ft_read_file(filename);
	scale_x = (double)WINDOW_WIDTH / (vars->map->width * 2);
	scale_y = (double)WINDOW_HEIGHT / (vars->map->height * 2);
	vars->map->scale_factor = fmax(scale_x, scale_y);
	vars->map->z_scale_factor = vars->map->scale_factor * 0.5;
}

void	setup_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"fdf - Wireframe Model");
	if (!vars->win)
		exit(EXIT_FAILURE);
	vars->img.img_ptr = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	vars->img.data = mlx_get_data_addr(vars->img.img_ptr, &vars->img.bpp,
			&vars->img.size_l, &vars->img.endian);
	ft_memset(vars->img.data, 0, WINDOW_HEIGHT * vars->img.size_l);
	draw_map(vars->map, &vars->img);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	mlx_key_hook(vars->win, handle_keypress, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_expose_hook(vars->win, render, vars);
}
