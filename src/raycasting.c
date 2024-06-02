#include "../includes/cub3d.h"

void setup_raycasting(t_game *game, t_ray *ray, int x) // this initialize some data about this current ray we'll trace
{
	ray->camera.x = 2 * x / (double)S_WIDTH - 1; // ray.camera.x is the x-coordinate on the Camera Plane (game->camera.plane) that the current X-coordinate of the screen represents.
	ray->dir.x = game->camera.dir.x + game->camera.plane.x * ray->camera.x; //ray.dir represents the direction vector that the ray will be casted, 
																			//calculated using the vector sum between the current camera direction vector and the ray.camera.x.
	ray->dir.y = game->camera.dir.y + game->camera.plane.y * ray->camera.x;
	ray->map.x = (int) game->camera.pos.x; // map.x and map.y are the TILE/SQUARE/BOX in our tiled world we are current in, the equivalent of the index in the map array;
	ray->map.y = (int) game->camera.pos.y;
}

void dda_setup(t_game *game, t_ray *ray) //this setup data for the DDA algorithm
{
	ray->hit = 0;
	// NOTE: For the DDA part is important that we understand that we keep the information of ther in the map grid we are (ray.map.x | ray.map.y) 
	// with integer as indexes and where inside that single square we are, so that we can calculate the distance between a certain floating point coordinate 
	// inside this square until the square side and so perform the step and see if it is a hit.
	ray->delta_dist.x = fabs(1 / ray->dir.x); //delta dist is the length of the ray from one x-side to the next x-side OR one y-side to the next y-side.
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1; //step defines the ritm and direction the DDA will jump in the calculation, it always jump 1 square 
						  //each iteration, but the sign represents the axle whe are going in the vector;
		ray->side_dist.x = (game->camera.pos.x - ray->map.x) * ray->delta_dist.x; //side_dist is the distance tha ray has to travel from its start position to the first 
		//side it should encounter. So X side_dist is the distance from the right/left sides it has to hit, if x direction is negative it will calculate the distance 
		//to the first side to the LEFT and if positive the first side to the RIGHT. 
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->camera.pos.x) * ray->delta_dist.x; 
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->camera.pos.y - ray->map.y) * ray->delta_dist.y; // Same logic of side_sit.x, but if y direction is negative it will calculate the 
																				//distance to the first side ABOVE, of it is positive the first side BELOW
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

void digital_diferencial_analysis(t_game *game, t_ray *ray, t_line *line) //this is de DDA algorithm, responsible to get the position where the ray will hit a wall
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
		if (game->map.map[ray->map.x][ray->map.y] != '0') //if the position we landed in the array is not an empty space, it means we have a hit, so we stop DDA and now have our ray data.
		{
			ray->hit = 1;
			if (ray->side == 0)
			{
				if (ray->step.x > 0)
					line->color = RGB_RED;
				else
					line->color = RGB_BLUE;
			}
			else
			{
				if (ray->step.y > 0)
					line->color = RGB_GREEN;
				else
					line->color = RGB_WHITE;
			}
		}
	}
}

void calculate_line(t_ray *ray, t_line *line)
{
	// First we calculate the perpendicular distance between the hitpoint and the camera plane
	// If the ray hited a x side (right/left)
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
	//if the ray hited a y side (down/up)
	else
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
	// NOTE: Our map is composed of X * Y tiles, each tile being a square:
	//         UP
	//       -----
	// LEFT  |   | RIGHT
	//       -----
	//        DOWN

	// Then we calculate the line data:
	//1. line.height: The height which the line will have when drawn
	line->height = (int) S_HEIGHT / ray->wall_dist;
	//2. the y coordinate of the first pixel of the line
	line->start = (-line->height / 2) + (S_HEIGHT / 2); // here S_HEIGHT /2 is because every wall center is at the center of the screen.
	if (line->start < 0) // if start point is beyond screen limits, cap it to the begin of the screen. Same for the end point and end of the screen.
		line->start = 0;
	//3. the y coordinate of the last pixel of the line
	line->end = (line->height / 2) + (S_HEIGHT / 2); 
	if (line->end >= S_HEIGHT)
		line->end = S_HEIGHT - 1;
	// Remember, we only calculate the y-start and the y-end because we always have the x-coordinates since the main raycasting loop iterates over each X stripe of the screen
}
