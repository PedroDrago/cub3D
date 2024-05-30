#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define RGB_RED    0xFF0000
#define RGB_GREEN  0x00FF00
#define RGB_BLUE   0x0000FF
#define RGB_WHITE  0xFFFFFF
#define RGB_YELLOW 0xFFFF0
# define RGB_PURPLE 0xA020F0
# define BROWN 0x964B00

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	my_mlx_pixel_put(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(t_image *img, int x, int start, int end, unsigned color)
{
	while (start <= end)
		my_mlx_pixel_put(img, x, start++, color);
}

int key_hook(int key, t_game *game)
{
	if (key == 65307)
		exit(1);
	if (key == 119) //w
	{
		game->data.posX += game->data.dirX * 0.5;
		game->data.posY += game->data.dirY * 0.5;
	}
	if (key == 97)
	{
		double oldDirx = game->data.dirX;
		game->data.dirX = game->data.dirX * cos(0.1) - game->data.dirY * sin(0.1);
		game->data.dirY = oldDirx * sin(0.1) + game->data.dirY * cos(0.1);
		double oldPlaneX = game->data.planeX;
		game->data.planeX = game->data.planeX * cos(0.1) - game->data.planeY * sin(0.1);
		game->data.planeY = oldPlaneX * sin(0.1) + game->data.planeY * cos(0.1);
	}
	if (key == 115) //s
	{
		game->data.posX -= game->data.dirX * 0.5;
		game->data.posY -= game->data.dirY * 0.5;
	}
	if (key == 100) //d
	{
		double oldDirx = game->data.dirX;
		game->data.dirX = game->data.dirX * cos(-0.1) - game->data.dirY * sin(-0.1);
		game->data.dirY = oldDirx * sin(-0.1) + game->data.dirY * cos(-0.1);
		double oldPlaneX = game->data.planeX;
		game->data.planeX = game->data.planeX * cos(-0.1) - game->data.planeY * sin(-0.1);
		game->data.planeY = oldPlaneX * sin(-0.1) + game->data.planeY * cos(-0.1);
	}
	return 0;
}

int game_loop(t_game *game)
{
	t_image frame;
	frame.img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, &frame.line_length, &frame.endian);
	//Paints ceiling and floor of different colors
	for (int x = 0; x < screenWidth; x++) {
		for (int y = 0; y < screenHeight / 2; y++) {
			my_mlx_pixel_put(&frame, x, y, RGB_PURPLE);
		}
		for (int y = screenHeight / 2; y < screenHeight; y++) {
			my_mlx_pixel_put(&frame, x, y, BROWN);
		}
	}
	for(int x = 0; x < screenWidth; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)screenWidth - 1; //x-coordinate in camera space
		double rayDirX = game->data.dirX + game->data.planeX * cameraX;
		double rayDirY = game->data.dirY + game->data.planeY * cameraX;
		int mapX = (int)game->data.posX;
		int mapY = (int)game->data.posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->data.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->data.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->data.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->data.posY) * deltaDistY;
		}
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		} 
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if(drawEnd >= screenHeight)drawEnd = screenHeight - 1;
		unsigned int color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = RGB_RED;  break; //red
			case 2:  color = RGB_GREEN;  break; //green
			case 3:  color = RGB_BLUE;   break; //blue
			case 4:  color = RGB_WHITE;  break; //white
			default: color = RGB_YELLOW; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		draw_line(&frame, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return 0;
}


int main(void)
{
	t_game	game;

	game.data.posX = 22, game.data.posY = 12;  //x and y start position
	game.data.dirX = -1, game.data.dirY = 0; //initial direction vector
	game.data.planeX = 0, game.data.planeY = 0.66; //the 2d raycaster version of camera plane
	game.data.time = 0; //time of current frame
	game.data.moveSpeed = 60 * 5.0;
	game.data.rotSpeed = 60 * 3.0;
	game.data.oldTime = 0; //time of previous frame
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 640, 480, "Cub3D");
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
