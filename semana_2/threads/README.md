# Threads in a Nutshell

## Introdução

Uma **thread** é a menor unidade de processamento que pode ser gerenciada de forma independente por um sistema operacional. As threads fazem parte de um processo e compartilham os mesmos recursos, como memória e descritores de arquivos, mas possuem seu próprio contexto de execução, incluindo um ponteiro de pilha e registradores.

Este documento aborda os conceitos fundamentais sobre threads, incluindo definições, vantagens, gerenciamento e exemplos práticos.

---

## O que é uma Thread?

Uma thread pode ser definida como:
- **Unidade de Execução**: Cada thread dentro de um processo pode executar independentemente.
- **Recursos Compartilhados**: As threads de um mesmo processo compartilham o espaço de endereço e os recursos do processo pai.
- **Contexto Próprio**: Cada thread possui seu próprio contador de programa, ponteiro de pilha e estado dos registradores.

---

## Vantagens do Uso de Threads

1. **Desempenho Melhorado**: Threads permitem a execução concorrente dentro de um processo, aproveitando CPUs multi-core.
2. **Compartilhamento de Recursos**: Como as threads compartilham memória, a comunicação entre elas é mais eficiente que entre processos.
3. **Responsividade**: Em aplicações interativas, threads permitem que partes do programa continuem responsivas enquanto outras realizam tarefas demoradas.
4. **Economia de Recursos**: A criação e troca de contexto entre threads consomem menos recursos do que entre processos.

---

## Gerenciamento de Threads

O gerenciamento de threads pode ser realizado de duas formas principais:

1. **Threads em Nível de Usuário**:
   - Gerenciadas pela aplicação sem envolver diretamente o kernel.
   - Mais leves, mas podem ter limitações no uso de múltiplos núcleos de CPU.

2. **Threads em Nível de Kernel**:
   - Gerenciadas pelo kernel do sistema operacional.
   - Podem aproveitar melhor os recursos do sistema, mas possuem maior overhead.

---

## Exemplos de Threads em C (usando pthreads)

### Exemplo Simples

Abaixo, um exemplo de criação de uma thread usando a biblioteca `pthread`:

```c
#include <stdio.h>
#include <pthread.h>

void* funcao_thread(void* arg) {
    printf("Thread executando: %s\n", (char*)arg);
    return NULL;
}

int main() {
    pthread_t thread;
    char* mensagem = "Olá, mundo!";

    // Criar uma nova thread
    if (pthread_create(&thread, NULL, funcao_thread, (void*)mensagem)) {
        fprintf(stderr, "Erro ao criar a thread\n");
        return 1;
    }

    // Aguardar a finalização da thread
    pthread_join(thread, NULL);

    printf("Thread finalizada.\n");
    return 0;
}
```

### Resultado:
- O programa cria uma thread que executa a função `funcao_thread` e imprime a mensagem fornecida.

---

## Sincronização de Threads

Como threads compartilham recursos, é necessário garantir que elas não acessem dados simultaneamente de maneira incorreta. As ferramentas mais comuns para sincronização incluem:

1. **Mutexes**: Impedem o acesso simultâneo a um recurso compartilhado.
2. **Semáforos**: Controlam o acesso a recursos com um contador.
3. **Barreiras**: Garantem que todas as threads cheguem a um ponto específico antes de continuar.

### Exemplo de Uso de Mutex:

```c
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int contador = 0;

void* incrementar(void* arg) {
    pthread_mutex_lock(&mutex);
    contador++;
    printf("Contador: %d\n", contador);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, incrementar, NULL);
    pthread_create(&t2, NULL, incrementar, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}
```
## Exemplos adicionais
Abaixo há exemplos dos conceitos relacionados ao assunto de Thread. Para compilar os mesmos, veja em [BUILD](../../BUILD.md)
- Exemplo contendo um deadlock: [Deadlock](./deadlock.c)
- Exemplo contendo uma abordagem de resolução de um deadlock: [Deadlock resolvido](./deadlock_resolved.c)
- Exemplo contendo uma abordagem de multithread simples: [Multithread](./multithread.c)
- Exemplo contendo uma abordagem monothread simples: [Monothread](./thread_simples.c)
- Exemplo contendo a utilização incorreta de um mutex: [Mutex errado](./mutex_wrong.c)
- Exemplo contendo a utilização correta de um mutex: [Mutex correto](./mutex_correct.c)
---

## Conclusão

Threads são fundamentais para desenvolver aplicações modernas que exigem execução concorrente. Ao dominar os conceitos de threads e suas técnicas de sincronização, é possível criar sistemas mais eficientes e responsivos.

Para mais informações, consulte:
- [Documentação do POSIX Threads](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- Livro: "Programming with POSIX Threads" de David R. Butenhof
- Livro: "Modern Operating Systems"/"Sistemas Operacionais Modernos" de Andrew Tanenbaum 5th edition

