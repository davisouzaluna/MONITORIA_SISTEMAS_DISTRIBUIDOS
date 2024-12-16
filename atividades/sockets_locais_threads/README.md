###  Aplicações Cliente e Servidor usando AF_UNIX  

Este projeto consiste em desenvolver duas aplicações simples de comunicação cliente-servidor utilizando sockets locais (`AF_UNIX`) em Python, Ruby ou C. Abaixo estão as especificações e requisitos detalhados para cada componente.

---

## **Descrição das Aplicações**

### **Cliente**
O cliente deve:
1. Conectar-se ao servidor.
2. Enviar, como primeira mensagem, um identificador único criativo (ex.: nome, ID gerado aleatoriamente, etc.).
3. Entrar em um loop para aguardar inputs do usuário.
4. A cada input do usuário, enviar a mensagem de texto ao servidor.

### **Servidor**
O servidor deve:
1. Aceitar conexões de múltiplos clientes simultaneamente.
2. Receber e armazenar o identificador único de cada cliente.
3. Para cada cliente, manter-se em um loop aguardando novas mensagens.
4. Exibir no console cada mensagem recebida, junto com o identificador do cliente que enviou a mensagem.

---

## **Requisitos Técnicos**
- Toda a comunicação entre cliente e servidor será realizada utilizando **sockets locais** (`AF_UNIX`).
- O servidor deve ser capaz de gerenciar conexões simultâneas de múltiplos clientes, podendo ser implementado com **threads**.
- Linguagens suportadas para a implementação:
  - **Python**
  - **Ruby**
  - **C**
- Nesse repositorio teremos apenas em **Python** e **C** pois o programador eh um tanto preguicoso
---

## **Dicas de Implementação**
1. **Entendimento do Código**
   - Leia e compreenda cada parte do código desenvolvido.
   - Certifique-se de saber o funcionamento de `AF_UNIX` e sockets em geral.
   
2. **Busca por Soluções**
   - Consulte **fontes externas** (como a documentação oficial da linguagem escolhida) para tirar dúvidas.
   - Caso tenha dificuldades específicas, utilize ferramentas de IA, como o ChatGPT, para receber explicações ou alternativas.

3. **Gerenciamento de Conexões**
   - Prefira o uso de **threads** para simplificar o gerenciamento de múltiplos clientes simultâneos.
   - Evite soluções baseadas em `select` ou conceitos avançados de sistemas operacionais que possam complicar o código.

4. **Validação e Depuração**
   - Realize testes em diferentes cenários para garantir que o servidor funcione corretamente com múltiplos clientes conectados.

---

## **Conselhos**
- **Documentação é essencial**: mantenha comentários explicativos no código para facilitar a compreensão.
- **Compartilhamento de dificuldades**: traga dúvidas ou desafios encontrados durante a implementação para discussões em aula.
- **Simples é melhor**: implemente soluções claras e diretas, utilizando as ferramentas e conceitos abordados na disciplina.

---

## **Como Rodar o Projeto**
### **Servidor**
1. Compile ou execute o programa do servidor.
   ```bash
   
   ```
2. O servidor estará aguardando conexões na *socket* local especificada.

### **Cliente**
1. Compile ou execute o programa do cliente.
   ```bash
   ```
2. Após conectar-se ao servidor, siga as instruções do console para enviar mensagens.

---

**Observação:**  
Traga qualquer dúvida ou implementação incompleta para aula, a fim de discutir e aprender com os colegas e o professor.

---
## Observações do Monitor

- O servidor em C foi feito para demonstrar o funcionamento de sockets `AF_UNIX` e `AF_INET`. O AF_UNIX é vinculado ao Sistema de arquivos, já o `AF_INET` recebe como parâmetro uma tupla contendo o IP-PORTA. A título de comparação, o `AF_UNIX` se aproxima de algo como o `AF_INET` em loopback. Entretanto, como a comunicação com `AF_INET` usa o tcp, ele carrega os algoritmos de congestionamento, controle de erro, backoffs e etc. Isso de um modo ou de outro é uma carga que o sistema precisa lidar(coisa que o `AF_UNIX`) 

- Também foi salvo os clientes(mais especificamente os id's) num arquivo de LOG para exercitar os conceitos de prevenção de impasses. Caso for criar uma thread para salvar os dados, e uma thread for esperar por outra para acessar um recurso, isso é chamado de impasse. Pra resolver isso, foi usado um mutex(`Mu`tual `Ex`clusion), que é basicamente um semáforo binário(só pode assumir dois valores). Pra prevenir ocorram bloqueios circulares(por exemplo, dois processos tem cada um o mutex que o outro precisa pra terminar a execução), que no nosso contexto são evitados através da liberação antecipada(quando algo dá errado ele já libera o mutex).

- Eu poderia fazer uma análise do id do cliente através do socket da conexão, mas para diminuir a complexidade desnecessária, o cliente envia tanto o ID quanto a mensagem que ele quer. 

- O CMake foi feito da maneira mais simplista possível

- Fiz em C pois ele deixa bem visivel as coisas que acontecem no SO. Eh chatinho(por causa dos ponteiros), mas eh bem legal pra demonstrar

