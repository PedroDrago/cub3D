# cub3d
Version: 10

### Blog
17/04/2024 04:38
Appearently raycasting is an algorithm to transoform a 2D view in a 3D view, so I guess the first step in this project would be building the 2D view of the game, and then applying raycasting on top of it. This will also be good for the Bonus part of the minimap, that will just be the 2D view of the game. But, I need to build the game already prepared to receive the raycasting, so for now I'll be studying really hard how raycasting works. 

Also I have a lot of doubts about smooth movements, tecnically I could just move the character like a did in so_long, tile by tile, but that is shit, so I seted as a personal goal that everything will have smooth movimentation in this game.

### Contents
- [Super Fast Ray Casting in Tiled Worlds using DDA](https://www.youtube.com/watch?v=NbSee-XM7WA)
- [Scratch a Pixel](https://www.scratchapixel.com/index.html)
- [raycasting article](https://lodev.org/cgtutor/raycasting.html)
- [Minilibx Content](https://github.com/qst0/ft_libgfx)
- [Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [John Carmack Talk](https://www.youtube.com/watch?v=lHLpKzUxjGk)
- [Programming a FPS From scratch](https://www.youtube.com/watch?v=fSjc8vLMg8c)

### Learn to use Funtions
```c
int	mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param);

int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
int	mlx_loop (void *mlx_ptr);
int mlx_loop_end (void *mlx_ptr);
int	mlx_hook(void *win_ptr, int x_event, int x_mask,
                 int (*funct)(), void *param);

int	mlx_do_key_autorepeatoff(void *mlx_ptr);
int	mlx_do_key_autorepeaton(void *mlx_ptr);
int	mlx_do_sync(void *mlx_ptr);

int	mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
int	mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
int	mlx_mouse_hide(void *mlx_ptr, void *win_ptr);
int	mlx_mouse_show(void *mlx_ptr, void *win_ptr);
```
