
#ifndef FDF_H
#define FDF_H

#include <fcntl.h>
#include "../libft/libft.h"
#include <stdlib.h>
#include <mlx.h>
#include <stdio.h>
# include <math.h>


// Define window dimensions and constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
// #define SCALE_FACTOR 20
// #define Z_SCALE_FACTOR 1
#define X_OFFSET (WINDOW_WIDTH / 2)
#define Y_OFFSET (WINDOW_HEIGHT / 2)



// Define ESC key code (adjust based on your system)
// #define ESC_KEY 53 // MacOS
#define ESC_KEY 65307 // Linux (X11)


typedef struct s_point {
    double x;
    double y;
    double z;
} t_point;


typedef struct s_map
{
    int width;
    int height;
    int **array;
	double scale_factor;
	double z_scale_factor;
}              t_map;

typedef struct s_img {
    void    *img_ptr;
    char    *data;
    int     bpp;
    int     size_l;
    int     endian;
} t_img;


// Function prototypes
t_map *ft_map_init(void);
t_map *ft_read_file(const char *filename);
int ft_get_width(const char *line);
int ft_get_height(const char *filename);
void ft_fill_row(int *row, char *line, int width);

void ft_iso_projection(double *x, double *y, double z);
t_point ft_get_point(int x, int y, t_map *map);
void ft_draw_line(t_point p0, t_point p1, t_img *img);
void draw_lines(t_map *map, int x, int y, t_img *img);
void draw_map(t_map *map, t_img *img);
void    put_pixel_to_img(t_img *img, int x, int y, int color);

int handle_keypress(int keycode);
int close_window();


#endif