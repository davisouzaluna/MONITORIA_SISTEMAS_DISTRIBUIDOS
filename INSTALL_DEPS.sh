#!/bin/bash

set -e  

# verificar permissões(sudo)
if [ "$(id -u)" -ne 0 ]; then
  echo "Por favor, execute este script como root ou com sudo."
  exit 1
fi

echo "Atualizando os pacotes..."
apt update

echo "Instalando CMake..."
apt install -y cmake

echo "Instalando GCC e Make (compilador e ferramentas de build)..."
apt install -y build-essential

echo "Instalando OpenSSL e bibliotecas de desenvolvimento..."
apt install -y libssl-dev

echo "Dependências instaladas com sucesso!"
