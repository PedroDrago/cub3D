#include "../includes/cub3d.h"

void	dda_data_setup(t_ray *ray, t_game *game)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->camera.pos.x
				- ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0
				- game->camera.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->camera.pos.y
				- ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0
				- game->camera.pos.y) * ray->delta_dist.y;
	}
}

void	dda_setup(t_game *game, t_ray *ray)
{
	ray->hit = 0;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	dda_data_setup(ray, game);
}

void	calculate_hit(t_ray *ray, t_line *line)
{
	ray->hit = 1;
	if (ray->side == 0)
	{
		if (ray->step.x > 0)
			line->color = NORTH;
		else
			line->color = SOUTH;
	}
	else
	{
		if (ray->step.y > 0)
			line->color = WEST;
		else
			line->color = EAST;
	}
}

void	digital_diferencial_analysis(t_game *game, t_ray *ray, t_line *line)
{
	dda_setup(game, ray);
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (game->map.map[ray->map.x][ray->map.y] == '1')
			calculate_hit(ray, line);
	}
}
