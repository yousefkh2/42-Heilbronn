/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:45:20 by yousef            #+#    #+#             */
/*   Updated: 2024/11/28 19:01:44 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		free_map(vars->map);
		cleanup_mlx(vars);
		exit(0);
	}
	return (0);
}

int	close_window(t_vars *vars)
{
	free_map(vars->map);
	cleanup_mlx(vars);
	exit(0);
	return (0);
}

int	render(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	return (0);
}
