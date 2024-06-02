#include "../includes/cub3d.h"

void	 my_mlx_pixel_put(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *img, int x, t_line line)
{
	while (line.start <= line.end)
		my_mlx_pixel_put(img, x, line.start++, line.color);
}
