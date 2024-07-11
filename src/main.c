#include "../includes/cub3d.h"
#include <stdio.h>

void	get_initial_pos(t_camera *camera, char **map)
{
	int	x;
	int y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while(map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
			{
				camera->pos.x = x;
				camera->pos.y = y;
				return ;
			}
			y++;
		}
		x++;
	}
	printf("Exiting at get_initial_pos\n");
	exit(1); //n achou deu merda, eh pra ter validado essa porra antes de chegar aqui (no momento ainda n esta validando).
}

void init_camera(t_camera *camera, t_game *game)
{
	//9/4
	camera->mov_speed = 0.5;
	camera->rot_speed = 0.2;
	get_initial_pos(camera, game->map.map);
	// NOTE: So that we can spawn the camera to the right direction (N, S, E, W) we need to alter camera.dir and camera.plane, just like in the rotation functions, 
	// but to a fixed value that would represent a 90 angle? idk, something like that, but I know that this current value makes tha camera looks to NORTH, 
	// so if we invert all the values to:
	// dir.x = 1
	// dir.y = 0
	// plane.x = 0
	// plane.y = -0.66
	// We should get a SOUTH directed camera. But for west and east I have no idea, i guess GPT could help with that.
	camera->dir.x = -1;
	camera->dir.y = 0;
	camera->plane.x = 0; 
	// NOTE: the camera plane representes the vector of where the camera exists. This is necessary because when drawing the ray, if the trace it directly 
	// to the player exatc point (pos.x, pos.y) all the rays will appear rounded, with the fish eye effect. This happens because when each point is traced directly to the player, 
	// each of them will have a calculated distance different from each other becuase of the player distance horizontal ditance to them, so the distance will 
	// increase respecting the horizontal position as well, and this cause each ray to have a different height not based on vertical distance but based on horizontal 
	// distance, and that causes the rounded effect.
	//NOTE:
	//--.---.---.---
	//  \   |   /
	//   \  |  /
	//    \ | /
	//     \|/
	//      P
	// In the above example we can visualize it. Both 3 points should appear the same height, because the are at the same vertical distance from the player, 
	// but because we trace them directly to the player x,y they will have different distances to it (straight line always the shortest path etc), so they'll 
	// be drawd with different heights.
	//--.---.---.---
	//  |   |   |
	//  |   |   |
	//  |   |   |
	//  |   |   |
	//------P------- -> Camera Plane
	// Here we trace them to the camera Plane instead of the Player, so we can see that both 3 points have the same distance from this plain, so will have the same height when drawed
	// This type of technique is not a fisheye correction, the fisheye is simply avoided by this way of calculating. It makes the calculations easier also, since whe don't 
	//even need to know the exact location where the wall was hit.
	camera->plane.y = 0.66;
}

int key_hook_down(int key, t_game *game)
{
	if (key == ESC)
		exit(1);
	if (key == W)
		game->keys[I_W] =  1;
	if (key == A)
		game->keys[I_A] =  1;
	if (key == S)
		game->keys[I_S] =  1;
	if (key == D)
		game->keys[I_D] =  1;
	if (key == LEFT)
		game->keys[I_LEFT] =  1;
	if (key == RIGHT)
		game->keys[I_RIGHT] = 1;
	return 0;
}

int key_hook_up(int key, t_game *game)
{
	if (key == ESC)
		exit(1);
	if (key == W)
		game->keys[I_W] =  0;
	if (key == A)
		game->keys[I_A] =  0;
	if (key == S)
		game->keys[I_S] =  0;
	if (key == D)
		game->keys[I_D] =  0;
	if (key == LEFT)
		game->keys[I_LEFT] =  0;
	if (key == RIGHT)
		game->keys[I_RIGHT] = 0;
	return 0;
}

void	update_camera(t_game *game)
{
	static    int    movement_limiter = 0;

	if (++movement_limiter == RATE)
	{
		movement_limiter = 0;
		if (game->keys[I_W])
			walk_forward(&game->camera, game->map.map);
		if (game->keys[I_A])
			walk_left(&game->camera, game->map.map);
		if (game->keys[I_S])
			walk_backwards(&game->camera, game->map.map);
		if (game->keys[I_D])
			walk_right(&game->camera, game->map.map);
		if (game->keys[I_LEFT])
			rotate_left(&game->camera);
		if (game->keys[I_RIGHT])
			rotate_right(&game->camera);
	}
}

void	draw_square(t_data *image, int y, int x, unsigned int color, int square_side)
{
	int i;
	int j;

	i = y;
	while(i < (y + square_side))
	{
		j = x;
		while(j < (x + square_side))
		{
			my_mlx_pixel_put(image, j, i, color);
			j++;
		}
		i++;
	}
}

int get_square_size(t_map *map)
{
	int width;
	int height;

	width = S_WIDTH/map->width;
	height = S_HEIGHT/map->height;

	if (width < height)
		return (width);
	return (height);
}

void	draw_map(t_game *game, t_data *tile)
{
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int square_side = get_square_size(&game->map);
	square_side /= 3;
	while(game->map.map[i])
	{
		j = 0;
		x = 0;
		while(game->map.map[i][j])
		{
			if (game->map.map[i][j] == ' ' || game->map.map[i][j] == '0')
				draw_square(tile, y, x, RGB_WHITE, square_side);
			else if (game->map.map[i][j] == '1')
				draw_square(tile, y, x, RGB_PURPLE, square_side);
			else
				draw_square(tile, y, x, RGB_GREEN, square_side);
			j++;
			x += square_side;
		}
		y += square_side;
		i++;
	}
}

t_data get_sprite(t_line line, t_game *game)
{
	t_data tex;

	if (line.color == NORTH)
		tex = game->textures[0];
	else if (line.color == SOUTH)
		tex = game->textures[1];
	else if (line.color == WEST)
		tex = game->textures[2];
	else
		tex = game->textures[3];
	return (tex);
}

int game_loop(t_game *game)
{
	int x;
	t_ray ray;
	t_data frame;
	t_line line;
	t_data sprite;

	x = 0;
	update_camera(game);
	frame.img = mlx_new_image(game->mlx, S_WIDTH, S_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, &frame.line_length, &frame.endian);
	draw_background(&frame);
	while (x < S_WIDTH) // for every vertical stripe on the screen we raycast
	{
		setup_raycasting(game, &ray, x);
		digital_diferencial_analysis(game, &ray, &line);
		calculate_line(&ray, &line);
		sprite = get_sprite(line, game);
		draw_line(&frame, x, line, &ray, game, &sprite);
		x++;
	}
	draw_map(game, &frame);
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return 0;
}

int main(int argc, char *argv[])
{
	t_game	game;
	// int wd;
	// int hg;
	// mlx_get_screen_size(game->mlx, &wd, &hg); // make some math with this to have dinamic sized window based on the monitor, and also define RATE based on the screen resolution

	if (argc != 2)
	{
		printf("Too much or too many arguments\n");
		exit(1);
	}
	ft_bzero(game.keys, 20);
	get_map(&game, argv[1]);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
	init_camera(&game.camera, &game);
	init_textures(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_hook_down, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &key_hook_up, &game);
	mlx_loop(game.mlx);
	return (0);
}
