#include "../includes/cub3d.h"
#include <stdio.h>

void	 my_mlx_pixel_put(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *img, int x, t_line line, t_ray *ray, t_game *game, t_data *texture)
{
	int y = line.start;
	int tex_y;
	int tex_x;
	int color;


	double wall_x;
	if (ray->side == 0)
		wall_x = game->camera.pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = game->camera.pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture->width);
	if (ray->side == 0 && ray->dir.x > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex_x = texture->width - tex_x - 1;

	// printf("wall dist: %f | dir.x: %f | dir.y: %f | cam.x: %f | cam.y: %f\n", ray->wall_dist, ray->dir.x, ray->dir.y, ray->camera.x, ray->camera.y);
	while (y <= line.end)
	{
		int d = y * 256 - S_HEIGHT * 128 + line.height * 128;
		tex_y = ((d * texture->height) / line.height) / 256;
		color = *(unsigned int*)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}

void	draw_background(t_data *frame, unsigned int ceil_rgb, unsigned int floor_rgb)
{
	int x;
	int y;

	// // TODO: esse algoritmo n eh o mais eficiente da pra ser pq ele desenha na tela inteira antes, inclusive onde haverao paredes. Pensei em na funcao draw line desenhar 
	//    tudo de uma vezJa la dentro a gnt sabe o start e o end da linha, eh so desenhar de 0 ate line.start com a cor do teto e de line.end ate S_HEIGHT com a cor do chao. 
	//    Tentei fazer mas da um segfault estranho quando colide com alguma parede direato quando o jogo inicia, n consegui resolver. Parece ter a ver com o mesmo problema de
	//    a camera atravessar a parede quando anda reto assim que o jogo comeca.
	x = 0;
	while (x < S_WIDTH)
	{
		y = 0;
		while (y <= S_HEIGHT / 2)
			my_mlx_pixel_put(frame, x, y++, ceil_rgb);
		while(y <= S_HEIGHT)
			my_mlx_pixel_put(frame, x, y++, floor_rgb);
		x++;
	}
}
