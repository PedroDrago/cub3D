/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrago <pdrago@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 19:17:21 by pdrago            #+#    #+#             */
/*   Updated: 2024/09/03 19:30:07 by pdrago           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	put_transparency(t_data *frame, t_data *texture, int x, int y)
{
	unsigned int	color;
	int				i;
	int				j;

	i = 0;
	while (i < texture->width)
	{
		j = 0;
		while (j < texture->height)
		{
			color = *(unsigned int *)(texture->addr
					+ (j * texture->line_length + i
						* (texture->bits_per_pixel / 8)));
			if (color != 4278190080)
				my_mlx_pixel_put(frame, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_weapon(t_game *game, t_data *frame)
{
	static int	weapon_frame = 0;
	t_data		*weapon_frame_data;

	weapon_frame_data = &game->weapon_sprites.frame1;
	if (game->is_shooting)
	{
		weapon_frame++;
		if (weapon_frame > 5 && weapon_frame < 10)
			weapon_frame_data = &game->weapon_sprites.frame2;
		else if (weapon_frame >= 10 && weapon_frame < 15)
			weapon_frame_data = &game->weapon_sprites.frame3;
		else if (weapon_frame >= 15)
		{
			if (weapon_frame == 25)
			{
				game->is_shooting = 0;
				weapon_frame = 0;
			}
			weapon_frame_data = &game->weapon_sprites.frame4;
		}
	}
	// FIX: Run this only 5 times at the start, one for each sprite
	put_transparency(frame, weapon_frame_data, S_WIDTH / 1.8, S_HEIGHT / 1.5);
}
