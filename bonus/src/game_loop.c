#include "../includes/cub3d.h"

void	get_sprite(t_line *line, t_game *game)
{
	if (line->color == NORTH)
		line->texture = &game->textures[0];
	else if (line->color == SOUTH)
		line->texture = &game->textures[1];
	else if (line->color == WEST)
		line->texture = &game->textures[2];
	else if (line->color == CLOSED)
		line->texture = &game->textures[CLOSED];
	else if (line->color == LUCAS)
		line->texture = &game->lucas;
	else if (line->color == FRAME)
		line->texture = &game->frame;
	else
		line->texture = &game->textures[3];
}

void	update_camera(t_game *game)
{
	static int	movement_limiter = 0;

	if (++movement_limiter == RATE)
	{
		movement_limiter = 0;
		if (game->keys[I_W])
			walk_forward(&game->camera, game->map.map, game->map.mini_map);
		if (game->keys[I_A])
			walk_left(&game->camera, game->map.map, game->map.mini_map);
		if (game->keys[I_S])
			walk_backwards(&game->camera, game->map.map, game->map.mini_map);
		if (game->keys[I_D])
			walk_right(&game->camera, game->map.map, game->map.mini_map);
		if (game->keys[I_LEFT])
			rotate_left(&game->camera);
		if (game->keys[I_RIGHT])
			rotate_right(&game->camera);
	}
}

void	pre_loop(t_game *game, t_data *frame)
{
	if (game->should_end)
	{
		mlx_loop_end(game->mlx);
		clean_exit(game);
	}
	update_camera(game);
	frame->img = mlx_new_image(game->mlx, S_WIDTH, S_HEIGHT);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bits_per_pixel,
			&frame->line_length, &frame->endian);
	draw_background(frame, game->map.ceiling_color, game->map.floor_color);
}

void	post_loop(t_game *game, t_data *frame)
{
	draw_map(game, frame);
	mlx_put_image_to_window(game->mlx, game->win, frame->img, 0, 0);
	mlx_destroy_image(game->mlx, frame->img);
}

int	game_loop(t_game *game)
{
	int		x;
	t_ray	ray;
	t_data	frame;
	t_line	line;

	x = 0;
	pre_loop(game, &frame);
	while (x < S_WIDTH)
	{
		setup_raycasting(game, &ray, x);
		digital_diferencial_analysis(game, &ray, &line);
		calculate_line(&ray, &line);
		get_sprite(&line, game);
		ray.x = x;
		draw_line(&frame, line, &ray, game);
		x++;
	}
	draw_weapon(game, &frame);
	post_loop(game, &frame);
	return (0);
}
