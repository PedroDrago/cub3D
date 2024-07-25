### Portas que abrem e fecham
Esse n sei qual a melhor forma, mas penso em algo de ter um caracter `D` no mapa para a porta, verificar se o personagem esta atualmente adjacente a essa porta, e se tiver, ai tem um evento pra tecla `E` que transforma esse caractere `D` em um caractere `O` representando porta aberta, ai a gnt ignora esse caractere nas colisoes e tambem muda a textura. talvez tb seja bom n permitir abrir/fechar a porta se o personagem estiver em cima de onde eh a porta.

### Animated Sprite
A ideia da arma la que vc @rafael deu, mas n sei como implementar, acho que vc tem alguma ideia por conta das suas animacoes na so_long

### Rotate the point of view with the mouse
Esse n deve ser dificil, nunca usei evento do mouse mas deve ter um eixo x,y, ai a gnt rotaciona baseado no eixo X, da p ver com alguma pessoa que usou o mouse ja, acho que o azevedo usou pro bonus da fdf.


### Ordem de render
1. teto e chao
2. raycasting
4. hud (minimapa)
3. arma


### Extra Bonus
acho que da p gnt fazer umas paradas maneiras que n dariam tanto trabalho:
- Correr: Esse é facil, acredito que apenas ter uma variavel com o modificador de velocidade tipo 1.5x. Ter um index no array de keys_pressed para o shift, e na hora de mover o personagem e multiplicar a posicao pelo mov_speed verificar se shift ta apertado, se estiver move move_speed * run_modifier.
- Musica
- Sound effects
- FPS counter
- Inimigos estaticos (n andam mas toman tiro e somem)
- Items que ficam jogados no chao que se passar em cima pega e muda algo na gameplay (uma bota que da mais speed, municao, etc, pra fazer o fundo ficar transparente da pra usar um artigo que um maluco da 42 sobre fazer imagens xpm ficarem com o fundo transparente ao inves de preto)

Mas esses seriam so se a gnt n tiver de saco cheio do projeto quando terminar o que tiver que fazer kkkkkkkkkkkk
