
#include "server.h"

void log_client_id(const char *identifier) {

    //bloqueia o mutex pra evitar impasse
    pthread_mutex_lock(&log_mutex);

    /*
    a struct FILE serve para representar um arquivo. Ela eh definida em FILE.h. Ela eh um ponteiro para uma estrutura que contem informacoes sobre o arquivo
    Se tu tiver com tempo livre tu acha a definicao dela dentro de stdio.h --> bits/types/FILE.h(import)
    */
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file == NULL) {
        perror("Erro ao abrir o arquivo de log");
        //desbloqueia o mutex caso algo de errado
        pthread_mutex_unlock(&log_mutex);
        return;
    }

    fprintf(log_file, "Cliente conectado: %s\n", identifier);
    fclose(log_file);
    //desbloqueia o mutex
    pthread_mutex_unlock(&log_mutex);
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);

    char identifier[256];
    char buffer[1024];

    // Recebe identificador único do cliente
    ssize_t bytes_received = recv(client_socket, identifier, sizeof(identifier) - 1, 0);
    if (bytes_received <= 0) {
        perror("Erro ao receber identificador");
        close(client_socket);
        return NULL;
    }
    identifier[bytes_received] = '\0'; // Garante o término da string
    printf("Cliente conectado: %s\n", identifier);

    // Salva o identificador no log
    log_client_id(identifier);

    // Loop para receber mensagens
    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        /*
        Para a definicao de `\0` veja o link: https://pt.stackoverflow.com/questions/177619/qual-a-diferen%C3%A7a-entre-null-0-e-0 
        */
        buffer[bytes_received] = '\0'; // Garante o término da string
        printf("Mensagem de %s: %s\n", identifier, buffer);
    }

    if (bytes_received == 0) {
        printf("Cliente %s desconectado.\n", identifier);
    } else {
        perror("Erro ao receber mensagem");
    }

    close(client_socket);
    return NULL;
}

/*
Conceitualmente, um socket e um ponto final de comunicacao entre dois pontos numa rede


*/

//O socket é um arquivo, então ele é um descritor de arquivo

int create_srv(int port, int buffer_size){

//================== Verificando os parametros de entrada ==================    
    if(port < 1024 || port > 65535){ // checando se a porta eh valida
        perror("Invalid port. Choose a port between 1024 and 65535");
        return -1;
    }
//=========================================================================

    int srv_socket; // declarando as variaveis de socket. 
    struct sockaddr_in srv_addr, client_addr; // declarando as variaveis de endereco
    int opt = 1; // variavel para setar as opcoes do socket(1 para ativar, 0 para desativar)
    socklen_t addrlen = sizeof(client_addr);
    //char *buffer[buffer_size]; // buffer para armazenar os dados recebidos(nao usei, mas caso queira responder o cliente vc usa esse buffer)

    /*Criando o socket

    AF_INET: Familia de protocolos de internet(IPV4)
    SOCK_STREAM: Tipo de socket que fornece uma conexao sequencial e confiavel(TCP)
    0: Protocolo padrao para o tipo de socket escolhido
    */
    if((srv_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){ // criando o socket. O erro vai entrar quando aparecer um valor negativo(nao existe socket com valor negativo)
        perror("socket failed"); //imprimindo erro
        return -1;
    }

  

    /*
    setsockopt: funcao para setar as opcoes do socket. Nesse caso vamos habilitar a reutilizacao de endereco e porta
    a funcao recebe como parametros:
    - o socket
    - o nivel do protocolo. No caso abaixo escolhemos a opcao SOL_SOCKET que e o nivel de socket padrao
    - a opcao que queremos setar. No caso abaixo escolhemos SO_REUSEADDR que permite reutilizar o endereco e a porta    
    - um ponteiro para o valor da opcao. No caso abaixo escolhemos 1 para ativar a opcao. Ela eh um ponteiro para a opcao acima
    - o tamanho do valor da opcao. Aqui eh so usar o sizeof()

    Habilitamos essa opcao para evitar erros como "Address already in use" que ocorre quando tentamos rodar o servidor em uma porta que ja esta sendo usada
    */
    if(setsockopt(srv_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))<0){
        perror("setsockopt(reuse ADDRESS) failed");
        return -1;
    }

    /*
    Abaixo tem mais exemplos de setsockopt, mas no caso de setar o tamanho do buffer de envio e recebimento(). Um buffer maior ocupa mais memoria, mas pode melhorar a performance. Um buffer menor ocupa menos memoria,
    mas pode piorar a performance com perda de pacotes. Cada aplicacao tem que testar o melhor tamanho de buffer para ela
    Nao coloquei no exemplo para executar para nao ocupar mais memoria desnecessariamente. Mas irei deixar abaixo um exemplo de como setar o tamanho do buffer. Brinque como quiser :)
    

    int sndbuf_size = 4096;
    if (setsockopt(client_socket, SOL_SOCKET, SO_SNDBUF, &sndbuf_size, sizeof(sndbuf_size)) < 0) {
        perror("Erro ao configurar SO_SNDBUF");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    int rcvbuf_size = 4096;
    if (setsockopt(client_socket, SOL_SOCKET, SO_RCVBUF, &rcvbuf_size, sizeof(rcvbuf_size)) < 0) {
        perror("Erro ao configurar SO_RCVBUF");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    
    */

   /*
   Aqui abaixo vamos atribuir os valores para a estrutura do endereco do servidor. A definicao dela eh:
    struct sockaddr_in {
          short            sin_family;   // e.g. AF_INET
          unsigned short   sin_port;     // e.g. htons(3490)
          struct in_addr   sin_addr;     // see struct in_addr, below
          char             sin_zero[8];  // zero this if you want to
     };
   */
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY; // bindando o socket a qualquer endereco disponivel
    srv_addr.sin_port = htons(port); // setando a porta do socket

    /*
    Fazendo o bind do socket ao endereco e porta
    */
    if(bind(srv_socket, (struct sockaddr *)&srv_addr, sizeof(srv_addr))<0){ // bindando o socket ao endereco e porta
        perror("bind failed");
        return -1;
    }

    /*
    Fazendo o socket escutar por conexoes

    */
    if(listen(srv_socket, 5) < 0){ // socket escutando por conexoes. O segundo parametro eh o numero maximo de conexoes pendentes/enfileiradas
        perror("listen failed");
        return -1;
    }

    printf("Servidor iniciado. Aguardando conexões...\n");
    while (1) { // Loop infinito para aceitar conexões
    int client_socket = accept(srv_socket, (struct sockaddr *)&client_addr, &addrlen); // Aceitando a conexão do cliente
    if (client_socket < 0) {
        perror("accept failed");
        return -1;
    }

    pthread_t thread_id; // Variável para a thread

    // Aloca memória para o socket do cliente
    int *client_socket_ptr = malloc(sizeof(int));
    if (client_socket_ptr == NULL) {
        perror("Failed to allocate memory for client socket");
        close(client_socket);
        continue;
    }

    *client_socket_ptr = client_socket; // Atribui o valor de client_socket à memória alocada

    // Criando a thread para lidar com o cliente
    if (pthread_create(&thread_id, NULL, handle_client, (void *)client_socket_ptr) != 0) {
        perror("Erro ao criar thread");
        close(client_socket);
        free(client_socket_ptr);
        continue;
    }

    pthread_detach(thread_id); // Detach para não precisar usar pthread_join
    }

    
    close(srv_socket);
    return 0; 
}

int create_srv_local(char *socket_path){
    
    if(socket_path == NULL){
        printf("socket path is %s/n", SOCKET_PATH);
        socket_path = SOCKET_PATH;
        return -1;
    }
    printf("socket path is %s\n", socket_path);
    unlink(socket_path); // removendo o arquivo de socket caso ele exista

    int srv_socket;
    struct sockaddr_un srv_addr; // declarando as variaveis de endereco(aka AF_UNIX)

    
    if((srv_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){ // criando o socket. O erro vai entrar quando aparecer um valor negativo(nao existe socket com valor negativo)
        perror("socket failed"); //imprimindo erro
        return -1;
    }

    //setando os bytes
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sun_family = AF_UNIX;

    //copia o caminho do socket para a estrutura do endereco. Em suma tamo alocando o endereco do socket pra struct srv_addr
    strncpy(srv_addr.sun_path, SOCKET_PATH, sizeof(srv_addr.sun_path) - 1);

   /*
   Pra eu nao ficar repetindo a msm coisa, nao vou comentar o que ja foi usado acima(dentro da funcao create_srv)
   */
    if(bind(srv_socket, (struct sockaddr *)&srv_addr, sizeof(srv_addr))<0){ 
        perror("bind failed");
        return -1;
    }

    if(listen(srv_socket, 5) < 0){ // socket escutando por conexoes. O segundo parametro eh o numero maximo de conexoes pendentes/enfileiradas
        perror("listen failed");
        return -1;
    }

    printf("Servidor iniciado. Aguardando conexões...\n");

    while(1){
        int *client_socket = malloc(sizeof(int));
        if((*client_socket = accept(srv_socket, NULL, NULL)) < 0){
            perror("Erro ao aceitar conexão");
            free(client_socket);
            continue;
        }

        pthread_t thread_id;
        if(pthread_create(&thread_id, NULL, handle_client,client_socket) != 0){
            perror("Erro ao criar thread");
            close(*client_socket);
            free(client_socket);
        }

        pthread_detach(thread_id);
    }

    close(srv_socket);
    unlink(SOCKET_PATH);
    return 0;
   
}


/*
Aqui eu ja estava cansado, ai pedi para o gpt gerar.
Depois eu so alterei alguns parametros para se aplicar no contexto da atividade

*/
int main(int argc, char *argv[]) {
    // Definindo valores padrão
    int buffer_size = BUFFER_SIZE;
    char *port_or_socket = NULL;

    // Verificando os argumentos da linha de comando
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <afinet|afunix> [port|socket_path] [buffer_size]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 3) {
        port_or_socket = argv[2];  // O caminho do socket ou a porta
    }
    
    if (argc == 4) {
        buffer_size = atoi(argv[3]);  // O tamanho do buffer
    }

    // Analisando o tipo de socket (AF_INET ou AF_UNIX)
    if (strcmp(argv[1], "afinet") == 0) {
        // Se for afinet, espera-se a porta como argumento
        if (port_or_socket == NULL) {
            fprintf(stderr, "Error: Port is required for AF_INET\n");
            exit(EXIT_FAILURE);
        }
        int port = atoi(port_or_socket);
        create_srv(port, buffer_size);  // Chama a função com AF_INET
    } else if (strcmp(argv[1], "afunix") == 0) {
        // Se for afunix, espera-se o caminho do socket como argumento
        if (port_or_socket == NULL) {
            port_or_socket = SOCKET_PATH;
        }
        create_srv_local(port_or_socket);  // Chama a função com AF_UNIX
    } else {
        fprintf(stderr, "Invalid argument. Use 'afinet' or 'afunix'.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}







