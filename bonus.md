### Bonus

Ideia pros bonus.

### Colisoes
ja temos

### Minimap
Percorrer array do mapa, e desenhar um quadrado para cada index do array, variando a cor dependendo do caractere:
```c
//Esboco de algo que deve fucnionar
	while(map[i])
	{
		j = 0;
		x = 0;
		while(map[i][j])
		{
			if (map[i][j] == ' ' || map[i][j] == '0')
				draw_square(&tile, y, x, RGB_WHITE);
			else if (map[i][j] == '1')
				draw_square(&tile, y, x, RGB_PURPLE);
			else
				draw_square(&tile, y, x, RGB_GREEN);
			j++;
			x += SQUARE_SIDE;
		}
		y += SQUARE_SIDE;
		i++;
	}
```
Tambem teria que modificar o array do mapa para ter a referencia de onde o jogador ta. Ideia: toda vez que se movimentar mudar o lugar novo para 'P' e o lugar antigo para o que era antes, igual logica da so_long. Essa parte acho que n vai ser tao facil, tentei fazer um esboco mas n consegui, mas de qualquer forma o pdf n eh especifico se precisa ter um indicador do personagem no mapa kkkkkkkkkk.

Outro problema eh escalar isso de acordo com o tamanho do mapa, nesse esboco de codigo acima se o mapa fosse mto grande ia ocupar a tela toda, entao acredito que `SQUARE_SIDE` tenha que ser uma variavel calculada de acordo com o tamanho da tela X tamanho do mapa, provavelmente uma divisao ou algo assim.

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
