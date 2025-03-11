/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:57:13 by ykhattab          #+#    #+#             */
/*   Updated: 2024/11/28 19:07:05 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = img->data + (y * img->size_l + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	digit;
	int	i;

	result = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i += 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digit = str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			digit = str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			digit = str[i] - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		result = result * base + digit;
		i++;
	}
	return (result);
}

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->points)
		{
			i = 0;
			while (i < map->height)
			{
				if (map->points[i])
					free(map->points[i]);
				i++;
			}
			free(map->points);
		}
		free(map);
	}
}

void	cleanup_mlx(t_vars *vars)
{
	if (vars->img.img_ptr)
		mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
}
