#include "../includes/cub3d.h"

void	setup_raycasting(t_game *game, t_ray *ray, int x)
{
	ray->camera.x = 2 * x / (double)S_WIDTH - 1;
	ray->dir.x = game->camera.dir.x + game->camera.plane.x * ray->camera.x;
	ray->dir.y = game->camera.dir.y + game->camera.plane.y * ray->camera.x;
	ray->map.x = (int) game->camera.pos.x;
	ray->map.y = (int) game->camera.pos.y;
}

void	calculate_line(t_ray *ray, t_line *line)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
	line->height = (int) S_HEIGHT / ray->wall_dist;
	line->start = (-line->height / 2) + (S_HEIGHT / 2);
	if (line->start < 0)
		line->start = 0;
	line->end = (line->height / 2) + (S_HEIGHT / 2);
	if (line->end >= S_HEIGHT)
		line->end = S_HEIGHT - 1;
}
