/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yousef <yousef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:48:09 by yousef            #+#    #+#             */
/*   Updated: 2024/11/23 01:57:27 by yousef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map *ft_map_init(void)
{
    t_map *map;

    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
    {
        perror("Error allocating memory for map");
        exit(EXIT_FAILURE);
    }
    map->width = 0;
    map->height = 0;
    map->array = NULL;
    return map;
}

t_map *ft_read_file(const char *filename)
{
    int fd;
    char *line;
    t_map *map;
    int i;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    map = ft_map_init();
    line = get_next_line(fd);
    if (!line)
    {
        perror("Error reading file or empty file");
        exit(EXIT_FAILURE);
    }
    map->width = ft_get_width(line);
    free(line);
    close(fd);
    map->height = ft_get_height(filename);
    map->array = (int **)malloc(sizeof(int *) * map->height);
    if (!map->array)
    {
        perror("Error allocating memory for map array");
        exit(EXIT_FAILURE);
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while ((line = get_next_line(fd)))
    {
        map->array[i] = malloc(sizeof(int) * map->width);
        if (!map->array[i])
        {
            perror("Error allocating memory for map row");
            exit(EXIT_FAILURE);
        }
        ft_fill_row(map->array[i], line, map->width);
        free(line);
        i++;
    }
    close(fd);
    return map;
}

int ft_get_width(const char *line)
{
	int width = 0;
	char **split_line;
	int i;

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
	return width;
}

int ft_get_height(const char *filename)
{
	int fd;
	int height = 0;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	return height;
}


void ft_fill_row(int *row, char *line, int width)
{
    char **split_line;
    int i;

    split_line = ft_split(line, ' ');
    if (!split_line)
    {
        perror("Error splitting line");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (i < width)
    {
        if (split_line[i])
            row[i] = ft_atoi(split_line[i]);
        else
            row[i] = 0;
        free(split_line[i]);
        i++;
    }
    while (split_line[i])
    {
        free(split_line[i]);
        i++;
    }
    free(split_line);
}

void put_pixel_to_img(t_img *img, int x, int y, int color)
{
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        char *dst = img->data + (y * img->size_l + x * (img->bpp / 8));
        *(unsigned int*)dst = color;
    }
}
