#!/bin/bash

# Caminho para a pasta que contém os arquivos
MAPS_DIR="tester-maps"

# Verifica se o diretório tester-maps existe
if [ ! -d "$MAPS_DIR" ]; then
    echo "O diretório $MAPS_DIR não existe."
    exit 1
fi

# Verifica se o programa cub3d está presente e é executável
if [ ! -x "./cub3D" ]; then
    echo "O programa cub3D não está presente ou não é executável."
    exit 1
fi

# Encontra todos os arquivos no diretório tester-maps e executa cub3d para cada um
find "$MAPS_DIR" -type f | while read -r file; do
    echo "Executando cub3D com o arquivo: $file"
    ./cub3D "$file"
done

