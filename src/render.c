#include "../includes/cub3d.h"
#include <stdio.h>

void	 my_mlx_pixel_put(t_data *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *img, int x, t_line line)
{
	int i;

	i = 0;
	while (i < line.start)
		my_mlx_pixel_put(img, x, i++, RGB_LIGHT_BLUE);
	while (line.start <= line.end)
		my_mlx_pixel_put(img, x, line.start++, line.color);
	while (line.end <= S_HEIGHT - 1)
		my_mlx_pixel_put(img, x, line.end++, RGB_BROWN);
}

void	draw_background(t_data *frame)
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
			my_mlx_pixel_put(frame, x, y++, RGB_LIGHT_BLUE);
		while(y <= S_HEIGHT)
			my_mlx_pixel_put(frame, x, y++, RGB_BROWN);
		x++;
	}
}
