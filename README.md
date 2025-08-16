# 📜 Get_Next_Line

Implementação da função "get_next_line", que retorna uma linha de um "file descriptor(fd)" por chamada.  
Projeto da 42 School que ensina manipulação de leitura de ficheiros, buffers, alocação dinâmica e vazamento de memória, variáveis estáticas...


## Funcionalidades

- Lê de um file descriptor ("fd") e retorna uma linha por chamada.
- Suporta:
  - Leitura de ficheiros;
  - Alocação dinâmica de memória;
  - Vazamento de memória(aprendi a trabalhar com o valgrind);
- Trabalha com o "BUFFER_SIZE" definido em tempo de compilação.
- Versão bónus : leitura em múltiplos file descriptors ao mesmo tempo.


## Estrutura do Projeto

- get_next_line.h
- get_next_line.c
- get_next_line_utils.c
- get_next_line_bonus.h
- get_next_line_bonus.c
- get_next_line_utils_bonus.c

## Como Compilar

Versão Normal:

cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl

Versão Bónus:

cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus

Execute :

./gnl  ./gnl_bonus

# Exemplo de Uso

#include "get_next_line.h"

#include <fcntl.h>

#include <stdio.h>

int main(void)
{
    
    int fd = open("teste.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}

# Exemplo de Saída:

Dado o ficheiro teste.txt:

Olá
42
Network

Execução:

Olá
42
Network


Autor: Eugênio Quintas
