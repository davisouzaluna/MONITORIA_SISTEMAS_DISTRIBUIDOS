# Processos, um breve resumo sobre:

## Introdução

Um **processo** é uma instância de um programa em execução. Ele é a unidade fundamental de execução em sistemas operacionais modernos e é composto por código executável, dados, contexto de execução, e outros recursos associados.

Este documento apresenta os conceitos essenciais sobre processos, abordando definições, estados, comunicação entre processos e exemplos práticos.

---

## O que é um Processo?

Um processo consiste em:
- **Código**: As instruções que o processador deve executar.
- **Memória**: Espaço alocado para dados e variáveis em uso.
- **Contexto de Execução**: Informações sobre o estado atual do processo, como os registradores e o contador de programa.
- **Recursos**: Arquivos abertos, dispositivos de entrada/saída e conexões de rede.

---

## Estados de um Processo

Os processos podem estar em diferentes estados durante seu ciclo de vida:

1. **Novo**: O processo foi criado, mas ainda não está em execução.
2. **Pronto**: O processo está preparado para ser executado, aguardando a disponibilidade da CPU.
3. **Executando**: O processo está em execução na CPU.
4. **Bloqueado**: O processo está aguardando algum evento (como entrada/saída).
5. **Encerrado**: O processo foi finalizado e seus recursos foram liberados.

---

## Gerenciamento de Processos

O gerenciamento de processos é responsabilidade do **escalonador de processos**, que determina:
- **Qual processo executar**: Usando algoritmos como Round Robin, Prioridade ou FIFO.
- **Alocação de recursos**: Incluindo CPU, memória e dispositivos.

---

## Comunicação entre Processos (IPC)

A comunicação entre processos é essencial em sistemas que executam múltiplas tarefas. Os métodos mais comuns de IPC incluem:
- **Sinais**: Para notificações simples entre processos.
- **Pipes**: Para transferência de dados de um processo para outro.
- **Sockets**: Para comunicação em redes.
- **Memória Compartilhada**: Para compartilhar informações de forma eficiente.

---

## Exemplo Prático (Em C)

Segue um exemplo de criação de processos usando a função `fork()` em C:

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Este é o processo filho (PID: %d)\n", getpid());
    } else if (pid > 0) {
        printf("Este é o processo pai (PID: %d)\n", getpid());
    } else {
        printf("Falha na criação do processo\n");
    }

    return 0;
}
```

### Resultado:
- O processo pai e o processo filho terão execuções independentes após o `fork()`.


## Exemplos adicionais
Abaixo há exemplos dos conceitos relacionados ao assunto de Processos. Para compilar os mesmos, veja em [BUILD](../../BUILD.md)

- Exemplificação dos estados de um processo utilizando a API `/proc` do Linux: [Estados de um processo](./process_states.c)

- Exemplificação do processo de criação de um processo, além da demonstração do conceito de hierarquização do mesmo: [Criação de processos](./create_process.c)



## Recursos Adicionais

Para mais informações, consulte:
- [Documentação do Linux](https://www.kernel.org/doc/)
- Livro: "Modern Operating Systems"/"Sistemas Operacionais Modernos" de Andrew Tanenbaum 5th edition

---


