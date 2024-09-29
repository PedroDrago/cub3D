#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data *img, t_line line, t_ray *ray, t_game *game)
{
	t_line_data	data;

	data.y = line.start;
	if (ray->side == 0)
		data.wall_x = game->camera.pos.y + ray->wall_dist * ray->dir.y;
	else
		data.wall_x = game->camera.pos.x + ray->wall_dist * ray->dir.x;
	data.wall_x -= floor(data.wall_x);
	data.tex_x = (int)(data.wall_x * (double)line.texture->width);
	if (ray->side == 0 && ray->dir.x > 0)
		data.tex_x = line.texture->width - data.tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		data.tex_x = line.texture->width - data.tex_x - 1;
	while (data.y <= line.end)
	{
		data.d = data.y * 256 - S_HEIGHT * 128 + line.height * 128;
		data.tex_y = ((data.d * line.texture->height) / line.height) / 256;
		data.color = *(unsigned int *)(line.texture->addr
				+ (data.tex_y * line.texture->line_length
					+data.tex_x * (line.texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(img, ray->x, data.y, data.color);
		data.y++;
	}
}

void	draw_background(t_data *frame
		, unsigned int ceil_rgb, unsigned int floor_rgb)
{
	int	x;
	int	y;

	x = 0;
	while (x < S_WIDTH)
	{
		y = 0;
		while (y <= S_HEIGHT / 2)
			my_mlx_pixel_put(frame, x, y++, ceil_rgb);
		while (y <= S_HEIGHT)
			my_mlx_pixel_put(frame, x, y++, floor_rgb);
		x++;
	}
}
