/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:44:44 by yousef            #+#    #+#             */
/*   Updated: 2024/11/28 19:42:59 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_width(const char *line)
{
	int		width;
	char	**split_line;
	int		i;

	width = 0;
	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		perror("Error splitting line");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
		width++;
	}
	free(split_line);
	return (width);
}

int	ft_get_height(const char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static void	ft_split_height_color(char *entry, int *height, int *color)
{
	char	**height_color;

	height_color = ft_split(entry, ',');
	if (!height_color)
	{
		perror("Error splitting height and color");
		exit(EXIT_FAILURE);
	}
	*height = ft_atoi(height_color[0]);
	if (height_color[1])
		*color = ft_atoi_base(height_color[1], 16);
	else
		*color = DEFAULT_COLOR;
	free(height_color[0]);
	if (height_color[1])
		free(height_color[1]);
	free(height_color);
}

void	ft_fill_row(t_point *row, char *line, t_map *map)
{
	char	**split_line;
	int		i;
	int		height;
	int		color;

	split_line = ft_split(line, ' ');
	i = 0;
	while (split_line[i] && i < map->width)
	{
		ft_split_height_color(split_line[i], &height, &color);
		row[i].z = height;
		row[i].color = color;
		i++;
	}
	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}
