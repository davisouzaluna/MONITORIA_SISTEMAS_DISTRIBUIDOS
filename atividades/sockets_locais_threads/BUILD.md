# Como Buildar o projeto na maquina ?

Nesse caso foi testada numa maquina Ubuntu, mas caso voce possua o `cmake` e `gcc` voce consegue executar


1. Primeiro instale as dependencias necessarias:
    ```bash
    sudo apt install cmake gcc -y
    ```
2. Crie um diretorio para salvar os executaveis

    ```bash
    mkdir build && cd build
    ```
3. Compile o projeto

    ```bash
    cmake .. && make
    ```
4. Agora os executaveis estao disponiveis. Abaixo eu mostro um exemplo de como executar o projeto utilizando `AF_UNIX`:
    - ## Servidor
        ```bash
        ./server afunix
        ```
    - ## Cliente
        ```bash
        ./client unix
        ```

5. Caso queira executar com `AF_INET`:

    - ## Servidor
        ```bash
        ./server afinet 9090
        ```
    - ## Cliente
        ```bash
        ./client tcp 127.0.0.1 9090
        ```

## Arquivo de log

Dentro do diretorio onde esta o executavel, existe um arquivo chamado `./server_log.txt`
