#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

void get_process_state(const char *pid) {
    char path[256], buffer[1024];
    FILE *stat_file;

    snprintf(path, sizeof(path), "/proc/%s/stat", pid);

    stat_file = fopen(path, "r");
    if (stat_file == NULL) {
        perror("Erro ao abrir o arquivo stat");
        return;
    }

    if (fgets(buffer, sizeof(buffer), stat_file) != NULL) {
        char state;
        sscanf(buffer, "%*d %*s %c", &state);
        
        //mapeamento dos estados
        const char *state_desc = NULL;
        switch (state) {
            case 'R': state_desc = "Em execução"; break;
            case 'S': state_desc = "Dormindo"; break;
            case 'D': state_desc = "Dormindo (espera ininterrupta)"; break;
            case 'Z': state_desc = "Zumbi"; break;
            case 'T': state_desc = "Parado"; break;
            case 'W': state_desc = "Esperando (paging)"; break;
            case 'X': state_desc = "Morto"; break;
            case 'P': state_desc = "Em espera de leitura"; break;
            default: state_desc = "Desconhecido"; break;
        }
        
        printf("Processo %s está no estado: %s\n", pid, state_desc);
    }

    fclose(stat_file);
}

int main() {
    struct dirent *entry;
    DIR *proc_dir;

    proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("Erro ao abrir /proc");
        return 1;
    }

    printf("Estados dos processos:\n");

    while ((entry = readdir(proc_dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            get_process_state(entry->d_name);
        }
    }

    closedir(proc_dir);
    return 0;
}

/*
Aqui eh usado a API /proc do Linux para obter os estados dos processos. Obviamente cada SO vai tratar de maneira diferente os estados

Simplificando, na funcao main acontece:
    1. Abre o diretorio /proc
    2. Le cada entrada do diretorio
    3. Se a entrada for um numero, chama a funcao get_process_state para obter o estado do processo
    4. Fecha o diretorio

Na funcao get_process_state:
    1. Monta o caminho do arquivo /proc/[pid]/stat
    2. Abre o arquivo stat
    3. Le a primeira linha do arquivo
    4. Pega o segundo campo da linha, que eh o estado do processo
    5. Mapeia o estado para uma descricao
    6. Imprime o estado do processo
    7. Fecha o arquivo

    exemplo de como o processo 1 do meu pc esta escrito(sudo nano /proc/1/stat):
        1 (systemd) S 0 1 1 0 -1 4194560 1163 0 0 0 0 0 0 0 20 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0
        1 eh o PID
        systemd eh o nome do processo
        S eh o estado do processo
        0 eh o PID do processo pai
        1 eh o grupo do processo
        1 eh o grupo da sessao
        0 eh o terminal de controle
        -1 eh o numero de threads
        4194560 eh o identificador do processo
        1163 eh o identificador do processo pai
        0 eh o identificador do grupo
        0 eh o identificador da sessao
        0 eh o terminal de controle
        0 eh o identificador do processo de controle
        0 eh o identificador do processo de controle
        0 eh o identificador do processo de controle
        20 eh a prioridade
        0 eh a nice
        1 eh o numero de threads
        0 eh o tempo de criação
        1 eh o tempo de usuario
        0 eh o tempo de sistema
        0 eh o tempo de espera
        0 eh o tempo de execucao
        0 eh o tempo de espera
*/
