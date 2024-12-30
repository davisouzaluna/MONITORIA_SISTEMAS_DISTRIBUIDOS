# Distributed File System

Um sistema de arquivos distribuido um sistema de arquivos que permite aos usuários acessar arquivos de dados de vários servidores em uma rede.
Os DFSs são usados ​​para armazenar, gerenciar e compartilhar grandes quantidades de dados em vários locais.


Alguns exemplos de **DFSs** incluem: 
- Sistema de arquivos distribuídos do Windows
- Sistema de arquivos de rede (NFS)
- Bloco de mensagens do servidor (SMB)
- Sistema de arquivos do Google (GFS)
- Lustre
- Sistema de arquivos distribuídos Hadoop (HDFS)
- GlusterFS
- Ceph
- MapR File System

---------------------------
Os DFSs são importantes porque permitem aos usuários: 

- Compartilhe recursos de armazenamento e arquivos de dados entre várias máquinas
- Acesse os mesmos dados de vários locais
- Gerencie big data em vários clusters
- Compartilhe dados e recursos de armazenamento remotamente
- Os DFSs podem ser projetados para permitir que usuários distribuídos geograficamente acessem e compartilhem arquivos remotamente como se estivessem armazenados localmente.

# Exemplo de sistema de arquivo distribuido

Nesse diretorio existe uma implementação mais simples possivel de um sistema de arquivo distribuido. Os requisitos sao:

- Comunicacao confiavel. Para isso usaremos o protocolo TCP/IP.
- A feature mínima é a troca de arquivos. Mas nesse exemplo usaremos uma abstração de uma camada acima(resumindo, não iremos manipular os arquivos propriamente ditos).
- Definicao do que é um arquivo nesse exemplo é um simples nome.
- Todo arquivo está organizado em diretórios, portanto também foi implementada essa estrutura de dados.


Não foi considerada/implementada na parte de comunicação:

- A organização dos bits(MSB e LSB)
- Para facilitar a explicação dos conceitos não foi utilizadas algumas convenções da linguagem.
- O sistema eh monothread

## Observações
Meu caro, **obviamente** a escolha de uma lista como estrutura de dados para o diretório **não** é a mais performática, pois as funções de busca são bastante prejudicadas.
Mas como o foco é na distribuição desse sistema na rede, então esse problema é **abstraído**. 