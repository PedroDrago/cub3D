#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

void update_map(char **map, t_vector_d fut_pos, int curr_x, int curr_y)
{
	if (curr_x != fut_pos.x || curr_y != fut_pos.y)
	{
		map[(int)fut_pos.x][(int)fut_pos.y] = 'P';
		map[(int)curr_x][(int)curr_y] = '0';
	}
}

int is_empty_tile(char c)
{
	return (c == '0' || c == 'P');
}

void	rotate_right(t_camera *camera)
{
	double old_dir_x;
	double old_plane_x;
	double rot;

	rot = camera->rot_speed;
	old_dir_x = camera->dir.x;
	old_plane_x = camera->plane.x;
	// NOTE:
	// First we rotate the camera->direciton vector
	// this is a matrix multiplication: of the current dir.vector for the following matrix:
	// [cos(a) -sin(1)] -> x
	// [sin(a) cos(a)] -> y
	// `a` being the rotation speed ( negative if rotating right)?
	camera->dir.x = camera->dir.x * cos(-rot) - camera->dir.y * sin(-rot);  //[dir.x * cos(a)] - [dir.y * sin(a)]
	camera->dir.y = old_dir_x * sin(-rot) + camera->dir.y * cos(-rot);     //[dir.x * sin(a)] + [dir.y * cos(a)]
	// NOTE: then we rotate the camera->plane vector
	camera->plane.x = camera->plane.x * cos(-rot) - (camera->plane.y * sin(-rot)); //[plane.x * cos(a)] - [plane.y * sin(a)]
	camera->plane.y = old_plane_x * sin(-rot) + camera->plane.y * cos(-rot);       //[plane.x * sin(a)] + [plane.y * cos(a)]
	return;
}

void	rotate_left(t_camera *camera)
{
	double old_dir_x;
	double old_plane_x;
	double rot;

	rot = camera->rot_speed;
	old_dir_x = camera->dir.x;
	old_plane_x = camera->plane.x;
	// NOTE: 
	// First we rotate the camera->direciton vector
	// this is a matrix multiplication: of the current dir.vector for the following matrix:
	// [cos(a) -sin(1)] -> x
	// [sin(a) cos(a)] -> y
	// `a` being the rotation speed ( negative if rotating right)?
	camera->dir.x = camera->dir.x * cos(rot) - camera->dir.y * sin(rot);  //[dir.x * cos(a)] - [dir.y * sin(a)]
	camera->dir.y = old_dir_x * sin(rot) + camera->dir.y * cos(rot);     //[dir.x * sin(a)] + [dir.y * cos(a)]
	// NOTE: then we rotate the camera->plane vector
	camera->plane.x = camera->plane.x * cos(rot) - (camera->plane.y * sin(rot)); //[plane.x * cos(a)] - [plane.y * sin(a)]
	camera->plane.y = old_plane_x * sin(rot) + camera->plane.y * cos(rot);       //[plane.x * sin(a)] + [plane.y * cos(a)]
	return;
}

int	get_diagonal_dir(t_vector_d pos, t_vector_d fut_pos)
{
	if (pos.x < fut_pos.x && pos.y < fut_pos.y)
		return (2);
	else if (pos.x < fut_pos.x && pos.y > fut_pos.y)
		return (1);
	else if (pos.x > fut_pos.x && pos.y > fut_pos.y)
		return (3);
	else if (pos.x > fut_pos.x && pos.y < fut_pos.y)
		return (4);
	return (0);
}

void walk_forward(t_camera *camera, char **map, char **minimap)
{
    t_vector_d fut_pos;
	int			diagonal_dir;

    // Calculate future position
    fut_pos.x = camera->pos.x + camera->dir.x * camera->mov_speed;
    fut_pos.y = camera->pos.y + camera->dir.y * camera->mov_speed;

	diagonal_dir = get_diagonal_dir(camera->pos, fut_pos);
	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
    // Convert current position to integer for indexing map
    int curr_x = (int)(camera->pos.x);
    int curr_y = (int)(camera->pos.y);

    // Check for collision with walls in x-direction
    if (!is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]))
		fut_pos.x = camera->pos.x;
	if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;

    // Check for collision with walls in y-direction
	if (!is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]))
		fut_pos.y = camera->pos.y;
	if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)] ))
        camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)] ))
        camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void walk_backwards(t_camera *camera, char **map, char **minimap)
{
    t_vector_d fut_pos;

    // Calculate future position
    fut_pos.x = camera->pos.x - camera->dir.x * camera->mov_speed;
    fut_pos.y = camera->pos.y - camera->dir.y * camera->mov_speed;

    // Convert current position to integer for indexing map
    int curr_x = (int)(camera->pos.x);
    int curr_y = (int)(camera->pos.y);


	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
    // Check for collision with walls in x-direction
    if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;

    // Check for collision with walls in y-direction
    if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]))
        camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]) )
        camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void walk_left(t_camera *camera, char **map, char **minimap)
{
    t_vector_d fut_pos;

    // Calculate future position perpendicular to camera direction
    fut_pos.x = camera->pos.x - camera->plane.x * camera->mov_speed;
    fut_pos.y = camera->pos.y - camera->plane.y * camera->mov_speed;

    // Convert current position to integer for indexing map
    int curr_x = (int)(camera->pos.x);
    int curr_y = (int)(camera->pos.y);


	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
    // Check for collision with walls in x-direction
    if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y])  && is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;

    // Check for collision with walls in y-direction
    if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]))
        camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]))
        camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}

void walk_right(t_camera *camera, char **map, char **minimap)
{
    t_vector_d fut_pos;

    // Calculate future position perpendicular to camera direction
    fut_pos.x = camera->pos.x + camera->plane.x * camera->mov_speed;
    fut_pos.y = camera->pos.y + camera->plane.y * camera->mov_speed;

    // Convert current position to integer for indexing map
    int curr_x = (int)(camera->pos.x);
    int curr_y = (int)(camera->pos.y);


	if (map[(int)(fut_pos.x)][(int)(fut_pos.y)] == '1')
		return ;
    // Check for collision with walls in x-direction
    if (camera->dir.x > 0.2 && is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;
	else if (camera->dir.x < 0.2 && is_empty_tile(map[(int)(fut_pos.x - 0.2)][curr_y]) && is_empty_tile(map[(int)(fut_pos.x + 0.2)][curr_y]))
        camera->pos.x = fut_pos.x;

    // Check for collision with walls in y-direction
    if (camera->dir.y > 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]))
        camera->pos.y = fut_pos.y;
	else if (camera->dir.y < 0.2 && is_empty_tile(map[curr_x][(int)(fut_pos.y - 0.2)]) && is_empty_tile(map[curr_x][(int)(fut_pos.y + 0.2)]) )
        camera->pos.y = fut_pos.y;
	update_map(minimap, fut_pos, curr_x, curr_y);
}
