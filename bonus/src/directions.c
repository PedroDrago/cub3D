#include "../includes/cub3d.h"

void	set_south(t_camera *camera)
{
	camera->dir.x = 1;
	camera->dir.y = 0;
	camera->plane.x = 0;
	camera->plane.y = -0.66;
}

void	set_north(t_camera *camera)
{
	camera->dir.x = -1;
	camera->dir.y = 0;
	camera->plane.x = 0;
	camera->plane.y = 0.66;
}

void	set_east(t_camera *camera)
{
	camera->dir.x = 0;
	camera->dir.y = 1;
	camera->plane.x = 0.66;
	camera->plane.y = 0;
}

void	set_west(t_camera *camera)
{
	camera->dir.x = 0;
	camera->dir.y = -1;
	camera->plane.x = -0.66;
	camera->plane.y = 0;
}
