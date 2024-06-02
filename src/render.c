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

void	draw_background(t_data *frame)
{
	int x;
	int y;

	x = 0;
	while (x < S_WIDTH)
	{
		y = 0;
		while (y <= S_HEIGHT / 2)
			my_mlx_pixel_put(frame, x, y++, RGB_LIGHT_BLUE);
		while(y <= S_HEIGHT)
			my_mlx_pixel_put(frame, x, y++, RGB_BROWN);
		x++;
	}
}
