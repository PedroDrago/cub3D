#include "../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

# define mapWidth 24
# define mapHeight 24
# define S_WIDTH 640
# define S_HEIGHT 480
# define RGB_RED    0xFF0000
# define RGB_GREEN  0x00FF00
# define RGB_BLUE   0x0000FF
# define RGB_WHITE  0xFFFFFF
# define RGB_YELLOW 0xFFFF0
# define RGB_PURPLE 0xA020F0
# define RGB_BROWN 0x964B00
# define W 119
# define LEFT 65361
# define RIGHT 65363
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define MOV_SPEED 0.5
# define ROT_SPEED 0.1

int    pressed_keys[5000];

char worldMap[mapWidth][mapHeight]=
{
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','2','2','2','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},
    {'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','3','0','0','0','3','0','0','0','1'},
    {'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','2','2','0','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','9','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','4','0','0','0','0','5','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','4','0','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
};


void	my_mlx_pixel_put(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_image *img, int x, int start, int end, unsigned color)
{
	while (start <= end)
		my_mlx_pixel_put(img, x, start++, color);
}

void	get_line(t_line *line, t_ray *ray)
{
	line->height = (int)(S_HEIGHT / ray->perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	line->start = -line->height / 2 + S_HEIGHT / 2;
	if (line->start < 0)
		line->start = 0;
	line->end = line->height / 2 + S_HEIGHT / 2;
	if (line->end >= S_HEIGHT)
		line->end = S_HEIGHT - 1;

	if (ray->side == 0 && ray->dir.x > 0)
		line->color = RGB_RED;
	else if (ray->side == 0 && ray->dir.x < 0)
		line->color = RGB_GREEN;
	else if (ray->side == 1 && ray->dir.y < 0)
		line->color = RGB_BLUE;
	//else if (ray->side == 0 && ray->dir.x > 0)
	//	line->color = RGB_WHITE;
	else
		line->color = RGB_YELLOW;
	//give x and y sides different brightness
	if (ray->side == 1)
		line->color = line->color / 2;
}

int	key_hook(int key, t_game *game) // <- atualizar essa
{
	(void)game;
	if (key == ESC)
		exit(1);
	if (key == W)
		pressed_keys[W] = !pressed_keys[W];
	if (key == A)
		pressed_keys[A] = !pressed_keys[A];
	if (key == S)
		pressed_keys[S] = !pressed_keys[S];
	if (key == D)
		pressed_keys[D] = !pressed_keys[D];
	if (key == LEFT)
		pressed_keys[113] = !pressed_keys[113]; // NOTE: Nao entendi que codigos sao esses 113 e 144. Foram indexes arbitrarios ja que o codigo passava do tamanho do array?
	if (key == RIGHT)
		pressed_keys[114] = !pressed_keys[114];
	return 0;
}

void	walk_foward(t_game *game)
{
	if (worldMap[(int)(game->data.pos.x + game->data.dir.x * game->data.mov_speed)][(int)game->data.pos.y] == '0')
		game->data.pos.x += game->data.dir.x * game->data.mov_speed;
	if (worldMap[(int)game->data.pos.x][(int)(game->data.pos.y + game->data.dir.y * game->data.mov_speed)] == '0')
		game->data.pos.y += game->data.dir.y * game->data.mov_speed;
}

void	walk_backwards(t_game *game)
{
	if (worldMap[(int)(game->data.pos.x - game->data.dir.x * game->data.mov_speed)][(int)game->data.pos.y] == '0')
		game->data.pos.x -= game->data.dir.x * game->data.mov_speed;
	if (worldMap[(int)game->data.pos.x][(int)(game->data.pos.y - game->data.dir.y * game->data.mov_speed)] == '0')
		game->data.pos.y -= game->data.dir.y * game->data.mov_speed;
}


void walk_left(t_game *game)
{
    double perp_dir_x = -game->data.dir.y;
    double perp_dir_y = game->data.dir.x;

    if (worldMap[(int)(game->data.pos.x + perp_dir_x * game->data.mov_speed)][(int)game->data.pos.y] == '0')
	game->data.pos.x += perp_dir_x * game->data.mov_speed;
    if (worldMap[(int)game->data.pos.x][(int)(game->data.pos.y + perp_dir_y * game->data.mov_speed)] == '0')
	game->data.pos.y += perp_dir_y * game->data.mov_speed;
}

void walk_right(t_game *game)
{
    double perp_dir_x = game->data.dir.y;
    double perp_dir_y = -game->data.dir.x;

    if (worldMap[(int)(game->data.pos.x + perp_dir_x * game->data.mov_speed)][(int)game->data.pos.y] == '0')
	game->data.pos.x += perp_dir_x * game->data.mov_speed;
    if (worldMap[(int)game->data.pos.x][(int)(game->data.pos.y + perp_dir_y * game->data.mov_speed)] == '0')
	game->data.pos.y += perp_dir_y * game->data.mov_speed;
}

void rotate_left(t_game *game)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->data.dir.x;
	game->data.dir.x = game->data.dir.x * cos(game->data.rot_speed) - game->data.dir.y * sin(game->data.rot_speed);
	game->data.dir.y = old_dir_x * sin(game->data.rot_speed) + game->data.dir.y * cos(game->data.rot_speed);
	old_plane_x = game->data.plane.x;
	game->data.plane.x = game->data.plane.x * cos(game->data.rot_speed) - game->data.plane.y * sin(game->data.rot_speed);
	game->data.plane.y = old_plane_x * sin(game->data.rot_speed) + game->data.plane.y * cos(game->data.rot_speed);
}

void rotate_right(t_game *game)
{
	double oldDirx = game->data.dir.x;
	game->data.dir.x= game->data.dir.x* cos(-game->data.rot_speed) - game->data.dir.y* sin(-game->data.rot_speed);
	game->data.dir.y= oldDirx * sin(-game->data.rot_speed) + game->data.dir.y* cos(-game->data.rot_speed);
	double oldPlaneX = game->data.plane.x;
	game->data.plane.x= game->data.plane.x* cos(-game->data.rot_speed) - game->data.plane.y* sin(-game->data.rot_speed);
	game->data.plane.y = oldPlaneX * sin(-game->data.rot_speed) + game->data.plane.y* cos(-game->data.rot_speed);
}

void    update_player_pos(t_game *game) // ESSA AQUI É NOVA
{
	if (pressed_keys[W])
		walk_foward(game);
	if (pressed_keys[A])
		walk_left(game);
	if (pressed_keys[S])
		walk_backwards(game);
	if (pressed_keys[D])
		walk_right(game);
	if (pressed_keys[113])
		rotate_left(game);
	if (pressed_keys[114])
		rotate_right(game);
}


void	paint_floor_and_ceiling(t_image *frame)
{
	int x;
	int y;

	x = 0;
	while (x < S_WIDTH)
	{
		y = 0;
		while (y <= (S_HEIGHT / 2))
			my_mlx_pixel_put(frame, x, y++, RGB_PURPLE);
		while (y < S_HEIGHT)
			my_mlx_pixel_put(frame, x, y++, RGB_BROWN);
		x++;
	}
}

void calculate_step_and_side_dist(t_game *game, t_ray *ray)
{
	//calculate step and initial sideDist
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->data.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->data.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->data.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->data.pos.y) * ray->delta_dist.y;
	}

}
void	digital_diferencial_analysis(t_ray *ray)
{
	while (ray->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
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
		//Check if ray->has hit a wall
		if (worldMap[ray->map.x][ray->map.y] > '0') ray->hit = 1;
	} 
}

void calculate_distance(t_ray *ray)
{
	if(ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
}

void calculate_pos_dir_delta(t_game *game,t_ray *ray, int x)
{
		//calculate ray position and direction
		ray->camera.x = 2 * x / (double)S_WIDTH - 1; //x-coordinate in camera space
		ray->dir.x = game->data.dir.x + game->data.plane.x * ray->camera.x;
		ray->dir.y = game->data.dir.y + game->data.plane.y * ray->camera.x;
		ray->map.x = (int)game->data.pos.x;
		ray->map.y = (int)game->data.pos.y;
		//length of ray from one x or y-side to next x or y-side
		if (ray->dir.x == 0)
			ray->delta_dist.x = 1e30;
		else
			ray->delta_dist.x = fabs(1 / ray->dir.x);
		if (ray->dir.y == 0)
			ray->delta_dist.y = 1e30;
		else
			ray->delta_dist.y = fabs(1 / ray->dir.y);
}

void	pre_raycast(t_game *game,t_image *frame)
{
	static    int    movement_limiter = 0;

	if (++movement_limiter == 6)
	{
		movement_limiter = 0;
		update_player_pos(game);
	}
	frame->img = mlx_new_image(game->mlx, S_WIDTH, S_HEIGHT);
	frame->addr = mlx_get_data_addr(frame->img, &frame->bits_per_pixel, &frame->line_length, &frame->endian);
	paint_floor_and_ceiling(frame);
}

int game_loop(t_game *game) // <- Atualizar essa aqui (só ta com a parte de cima da função, o resto pode deixar igual.
{
	t_image frame;
	t_ray ray;
	t_line line;
	int	x;

	x = 0;
	pre_raycast(game, &frame);
	while(x < S_WIDTH)
	{
		calculate_pos_dir_delta(game, &ray, x);
		ray.hit = 0;  
		calculate_step_and_side_dist(game, &ray);
		digital_diferencial_analysis(&ray);
		calculate_distance(&ray);
		get_line(&line, &ray);
		draw_line(&frame, x, line.start, line.end, line.color);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	return 0;
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	count;
	char	*ptr;

	count = 0;
	ptr = (char *) s;
	while (count < n)
	{
		ptr[count] = c;
		count++;
	}
	return (s);
}

int main(int argc, char *argv[])
{
	t_game	game;


	t_map map_data;
	map_data.file_height = 0;
	map_data.file_width = 0;
	if (argc != 2)
	{
		printf("Too much or too many arguments\n");
		exit(1);
	}
	get_map_proportions(&map_data, argv[1]);
	read_map_file(&map_data, argv[1]);
	parse_map(&map_data);
	print_map_data(&map_data);
	// WARN: Tudo acima é codigo do parser que está no arquivo novo parser.c.

	ft_memset(pressed_keys, 0, sizeof(pressed_keys)); //  <-        ADICIONAR ESSA
	game.map = &map_data;
	game.data.pos.x = 22, game.data.pos.y = 12;  //x and y start position
	game.data.dir.x = -1, game.data.dir.y = 0; //initial direction vector
	game.data.plane.x = 0, game.data.plane.y = 0.66; //the 2d raycaster version of camera plane
	game.data.mov_speed = 0.5;
	game.data.rot_speed = 0.1;
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 640, 480, "Cub3D");
	mlx_loop_hook(game.mlx, game_loop, &game);
	//mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &key_hook, 0); // <- ADICIONAR ESSA
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &key_hook, 0); //<- ADICIONAR ESSA
	mlx_loop(game.mlx);
	return (0);
}
