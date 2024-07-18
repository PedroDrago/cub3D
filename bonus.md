### Bonus

Ideia pros bonus.

### Colisoes
ja temos

### Minimap
Percorrer array do mapa, e desenhar um quadrado para cada index do array, variando a cor dependendo do caractere:
```c
//Esboco de algo que deve fucnionar
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
```
Tambem teria que modificar o array do mapa para ter a referencia de onde o jogador ta. Ideia: toda vez que se movimentar mudar o lugar novo para 'P' e o lugar antigo para o que era antes, igual logica da so_long. Essa parte acho que n vai ser tao facil, tentei fazer um esboco mas n consegui, mas de qualquer forma o pdf n eh especifico se precisa ter um indicador do personagem no mapa kkkkkkkkkk.

### Portas que abrem e fecham
Esse n sei qual a melhor forma, mas penso em algo de ter um caracter `D` no mapa para a porta, verificar se o personagem esta atualmente adjacente a essa porta, e se tiver, ai tem um evento pra tecla `E` que transforma esse caractere `D` em um caractere `O` representando porta aberta, ai a gnt ignora esse caractere nas colisoes e tambem muda a textura. talvez tb seja bom n permitir abrir/fechar a porta se o personagem estiver em cima de onde eh a porta.

### Animated Sprite
A ideia da arma la que vc @rafael deu, mas n sei como implementar, acho que vc tem alguma ideia por conta das suas animacoes na so_long

### Rotate the point of view with the mouse
Esse n deve ser dificil, nunca usei evento do mouse mas deve ter um eixo x,y, ai a gnt rotaciona baseado no eixo X, da p ver com alguma pessoa que usou o mouse ja, acho que o azevedo usou pro bonus da fdf.


### Ordem de render
1. teto e chao
2. raycasting
3. arma
4. hud (minimapa)


### Extra Bonus
acho que da p gnt fazer umas paradas maneiras que n dariam tanto trabalho:
- Correr: Esse é facil, acredito que apenas ter uma variavel com o modificador de velocidade tipo 1.5x. Ter um index no array de keys_pressed para o shift, e na hora de mover o personagem e multiplicar a posicao pelo mov_speed verificar se shift ta apertado, se estiver move move_speed * run_modifier.
- Musica
- Sound effects
- FPS counter
- Inimigos estaticos (n andam mas toman tiro e somem)
- Items que ficam jogados no chao que se passar em cima pega e muda algo na gameplay (uma bota que da mais speed, municao, etc, pra fazer o fundo ficar transparente da pra usar um artigo que um maluco da 42 sobre fazer imagens xpm ficarem com o fundo transparente ao inves de preto)

Mas esses seriam so se a gnt n tiver de saco cheio do projeto quando terminar o que tiver que fazer kkkkkkkkkkkk
