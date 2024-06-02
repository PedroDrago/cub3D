#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define S_WIDTH 640
# define S_HEIGHT 480
# define RGB_RED    0xFF0000
# define RGB_GREEN  0x00FF00
# define RGB_BLUE   0x0000FF
# define RGB_WHITE  0xFFFFFF
# define RGB_YELLOW 0xFFFF0
# define RGB_PURPLE 0xA020F0
# define RGB_BROWN 0x964B00
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

char worldMap[MAP_WIDTH][MAP_HEIGHT]=
{
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','1','1','1','1','1','0','0','0','0','1','0','1','0','1','0','0','0','1'},
    {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','1','0','0','0','1','0','0','0','1'},
    {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','1','1','0','1','1','0','0','0','0','1','0','1','0','1','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','P','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','0','0','0','0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','0','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
};


void	 my_mlx_pixel_put(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_image *img, int x, int line_start, int line_end, unsigned int color)
{
	while (line_start <= line_end)
		my_mlx_pixel_put(img, x, line_start++, color);
}

// # define MAP_WIDTH 24
// # define MAP_HEIGHT 24
// # define S_WIDTH 640
// # define S_HEIGHT 480

void init_camera(t_camera *camera)
{
	camera->pos.x = 22;
	camera->pos.y =  12;
	camera->plane.x = 0; // the camera plane representes the vector of where the camera exists. This is necessary because when drawing the ray, if the trace it directly to the player exatc point (pos.x, pos.y) all the rays will appear rounded, with the fish eye effect. This happens because when each point is traced directly to the player, each of them will have a calculated distance different from each other becuase of the player distance horizontal ditance to them, so the distance will increase respecting the horizontal position as well, and this cause each ray to have a different height not based on vertical distance but based on horizontal distance, and that causes the rounded effect.
	//--.---.---.---
	//  \   |   /
	//   \  |  /
	//    \ | /
	//     \|/
	//      P
	// In the above example we can visualize it. Both 3 points should appear the same height, because the are at the same vertical distance from the player, but because we trace them directly to the player x,y they will have different distances to it (straight line always the shortest path etc), so they'll be drawd with different heights.
	//--.---.---.---
	//  |   |   |
	//  |   |   |
	//  |   |   |
	//  |   |   |
	//------P------- -> Camera Plane
	// Here we trace them to the camera Plane instead of the Player, so we can see that both 3 points have the same distance from this plain, so will have the same height when drawed
	//
	camera->plane.y = 0.66;
}

int key_handler(int key, t_game *game)
{
	if (key == ESC)
		exit(1);
	return 0;
}

void dda_setup(t_game *game, t_ray *ray) //this setup data for the DDA algorithm
{
	// For the DDA part is important that we understand that we keep the information of ther in the map grid we are (ray.map.x | ray.map.y) with integer as indexes and where inside that single square we are, so that we can calculate the distance between a certain floating point coordinate inside this square until the square side and so perform the step and see if it is a hit.
	ray->delta_dist.x = fabs(1 / ray->dir.x); //delta dist is the length of the ray from one x-side to the next x-side OR one y-side to the next y-side.
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1; //step defines the ritm and direction the DDA will jump in the calculation, it always jump 1 square each iteration, but the sign represents the axle whe are going in the vector;
		ray->side_dist.x = (game->camera.pos.x - ray->map.x) * ray->delta_dist.x; //side_dist is the distance tha ray has to travel from its start position to the first side it should encounter. So X side_dist is the distance from the right/left sides it has to hit, if x direction is negative it will calculate the distance to the first side to the LEFT and if positive the first side to the RIGHT. 
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->camera.pos.x) * ray->delta_dist.x; 
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->camera.pos.y - ray->map.y) * ray->delta_dist.y; // Same logic of side_sit.x, but if y direction is negative it will calculate the distance to the first side ABOVE, of it is positive the first side BELOW
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->camera.pos.y) * ray->delta_dist.y;
	}
	// NOTE:
	//           +y
	//            |
	//            |
	//            |
	//            |
	// -x---------.---------+x
	//            |             
	//            |             
	//            |             
	//            |             
	//           -y             
}

void digital_diferencial_analysis(t_game *game, t_ray *ray) //this is de DDA algorithm, responsible to get the position where the ray will hit a wall
{
	dda_setup(game, ray);
	while (ray->hit == 0) //each iteration we jump 1 square in in a direaction (x or y).
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x; // this is incrementing the floating point data (delta being the ammount it lacks to reach the next side)
			ray->map.x += ray->step.x; // this is incrementing/decrementing the integer position in the map array by 1 square (step may be -1 or 1 depending on direction, remember)
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (worldMap[ray->map.x][ray->map.y] != '0') //if the position we landed in the array is not an empty space, it means we have a hit, so we stop DDA and now have our ray data.
			ray->hit = 1;
	}
}

void setup_raycasting(t_game *game, t_ray *ray, int x) // this initialize some data about this current ray we'll trace
{
	ray->camera.x = 2 * x / (double)S_WIDTH - 1; // ray.camera.x is the x-coordinate on the Camera Plane (game->camera.plane) that the current X-coordinate of the screen represents.
	ray->dir.x = game->camera.dir.x + game->camera.dir.y * ray->camera.x; //ray.dir represents the direction vector that the ray will be casted, calculated using the vector sum between the current camera direction vector and the ray.camera.x.
	ray->map.x = (int) game->camera.pos.x; // map.x and map.y are the TILE/SQUARE/BOX in our tiled world we are current in, the equivalent of the index in the map array;
	ray->map.y = (int) game->camera.pos.y;
}

int game_loop(t_game *game)
{
	int x;
	t_ray ray;

	x = 0;
	while (x < S_WIDTH) // for every vertical stripe on the screen we raycast
	{
		setup_raycasting(game, &ray, x);
		digital_diferencial_analysis(game, &ray);
	}
	return 0;
}


int main(int argc, char *argv[])
{
	t_game	game;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 640, 480, "Cub3D");

	init_camera(&game.camera);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_loop(game.mlx);
	return (0);
}
