#include "../includes/cub3d.h"

void init_camera(t_camera *camera)
{
	//9/4
	camera->mov_speed = 0.5;
	camera->rot_speed = 0.2;
	// camera->pos.x = 22;
	// camera->pos.y =  12;
	camera->pos.x = 9;
	camera->pos.y = 4;
	camera->dir.x = -1;
	camera->dir.y = 0;
	camera->plane.x = 0; //the camera plane representes the vector of where the camera exists. This is necessary because when drawing the ray, if the trace it directly to the player exatc point (pos.x, pos.y) all the rays will appear rounded, with the fish eye effect. This happens because when each point is traced directly to the player, each of them will have a calculated distance different from each other becuase of the player distance horizontal ditance to them, so the distance will increase respecting the horizontal position as well, and this cause each ray to have a different height not based on vertical distance but based on horizontal distance, and that causes the rounded effect.
	//NOTE:
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
	// This type of technique is not a fisheye correction, the fisheye is simply avoided by this way of calculating. It makes the calculations easier also, since whe don't even need to know the exact location where the wall was hit.
	camera->plane.y = 0.66;
}


int key_hook(int key, t_game *game)
{
	if (key == ESC)
		exit(1);
	if (key == W)
		game->keys[I_W] = !game->keys[I_W];
	if (key == A)
		game->keys[I_A] = !game->keys[I_A];
	if (key == S)
		game->keys[I_S] = !game->keys[I_S];
	if (key == D)
		game->keys[I_D] = !game->keys[I_D];
	if (key == LEFT)
		game->keys[I_LEFT] = !game->keys[I_LEFT];
	if (key == RIGHT)
		game->keys[I_RIGHT] = !game->keys[I_RIGHT];
	return 0;
}

void	update_camera(t_game *game)
{
	static    int    movement_limiter = 0;

	if (++movement_limiter == 15)
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

int game_loop(t_game *game)
{
	int x;
	t_ray ray;
	t_data frame;
	t_line line;

	x = 0;
	update_camera(game);
	frame.img = mlx_new_image(game->mlx, S_WIDTH, S_HEIGHT);
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, &frame.line_length, &frame.endian);
	while (x < S_WIDTH) // for every vertical stripe on the screen we raycast
	{
		setup_raycasting(game, &ray, x);
		digital_diferencial_analysis(game, &ray);
		calculate_line(&ray, &line);
		draw_line(&frame, x, line);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return 0;
}

void	get_map(t_game *game, char *file)
{
	game->map.file_height = 0;
	game->map.file_width = 0;
	get_map_proportions(&game->map, file);
	read_map_file(&game->map, file);
	parse_map(&game->map);
	// print_map_data(&game->map);
	print_split(game->map.map);
}

int main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		printf("Too much or too many arguments\n");
		exit(1);
	}
	ft_bzero(game.keys, 20);
	get_map(&game, argv[1]);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 640, 480, "Cub3D");
	init_camera(&game.camera);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_hook, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &key_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
