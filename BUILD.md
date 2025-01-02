# Buildar o projeto sem o Docker


## Requerimentos

- Versão mínima do Ubuntu `22.04 LTS` --> WSL `FUNCIONA`.
- GCC
- CMake

Caso você somente tenha o ubuntu ou wsl, execute o comando abaixo para instalar o gcc e cmake:

```bash
sudo apt update &&
sudo apt install -y build-essential gcc cmake
```

## Passo a passo:

1. Crie um diretório `build` dentro da pasta raiz do projeto. Esse diretório é onde seu executável estará salvo.
    ```bash
    mkdir build && cd build
    ```
2. Dentro do diretório `build` execute o comando abaixo para compilar e criar os executáveis:

    ```bash
    cmake .. && make
    ```
Agora compilado todos os arquivos, você pode navegar e executar os exemplos