/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhattab <ykhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:48:09 by yousef            #+#    #+#             */
/*   Updated: 2024/11/28 19:34:37 by ykhattab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*ft_read_file(const char *filename)
{
	int		fd;
	t_map	*map;

	fd = open_file(filename);
	map = initialize_map_and_width(fd);
	close(fd);
	map->height = ft_get_height(filename);
	map->points = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->points)
	{
		perror("Error allocating memory for map array");
		exit(EXIT_FAILURE);
	}
	fd = open_file(filename);
	read_map_data(fd, map);
	close(fd);
	return (map);
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_map	*initialize_map_and_width(int fd)
{
	t_map	*map;
	char	*line;

	map = ft_map_init();
	line = get_next_line(fd);
	if (!line)
	{
		perror("Error reading file or empty file");
		exit(EXIT_FAILURE);
	}
	map->width = ft_get_width(line);
	free(line);
	return (map);
}

void	read_map_data(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->points[i] = malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
		{
			perror("Error allocating memory for map row");
			exit(EXIT_FAILURE);
		}
		ft_fill_row(map->points[i], line, map);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

t_map	*ft_map_init(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
	{
		perror("Error allocating memory for map");
		exit(EXIT_FAILURE);
	}
	map->width = 0;
	map->height = 0;
	map->points = NULL;
	map->scale_factor = 1.0;
	map->z_scale_factor = 1.0;
	return (map);
}
