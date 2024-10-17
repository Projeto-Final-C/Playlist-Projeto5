#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura Musica
typedef struct Musica
{
    char titulo[50];
    char artista[50];
    int favorita;
} Musica;

// Função que vai ler as entradas do usuário
int lerEntrada(const char *mensagem)
{
    char entrada[50];
    int opcao;

    printf("%s", mensagem);
    fgets(entrada, sizeof(entrada), stdin);
    if (sscanf(entrada, "%d", &opcao) != 1)
    {
        printf("Opcao invalida. Tente novamente !\n");
        opcao = -1; // Resetar "opcao"
    }

    return opcao;
}

// Coloquei essa primeira parte de inserir músicas na playlist.
void inserirMusica(struct Musica **playlist, int *numMusicas, int *tamanhoPlaylist)
{
    // Se a playlist estiver cheia, realocamos mais espaço
    if (*numMusicas == *tamanhoPlaylist)
    {
        *tamanhoPlaylist *= 2; // Dobramos o tamanho da playlist
        *playlist = realloc(*playlist, *tamanhoPlaylist * sizeof(struct Musica));
        if (*playlist == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            return;
        }
    }

    struct Musica novaMusica;

    // Solicitando ao usuário o informações das músicas
    printf("Digite o titulo da musica: ");
    scanf(" %[^\n]", novaMusica.titulo);
    getchar(); // Limpando entrada

    printf("Digite o nome do artista: ");
    scanf(" %[^\n]", novaMusica.artista);
    getchar(); // Limpando entrada

    novaMusica.favorita = 0;

    // Inserindo a nova música na playlist
    (*playlist)[*numMusicas] = novaMusica;
    (*numMusicas)++;

    printf("Musica inserida com sucesso !\n");
}

// Coloquei essa função, que só vai mostrar as músicas na playlist msm!!!
void mostrarPlaylist(struct Musica **playlist, int numMusicas)
{
    // Verificando se a playlist está vazia
    if (numMusicas == 0)
    {
        printf("\nA sua playlist esta vazia.\n");
        return;
    }

    printf("\nPlaylist:\n");

    for (int i = 0; i < numMusicas; i++)
    {
        // Mostrando as informações das músicas
        printf("%d. %s - %s", i + 1, (*playlist)[i].titulo, (*playlist)[i].artista);

        // Verificando se a música é favorita
        if ((*playlist)[i].favorita)
        {
            printf(" (Favoritada)");
        }
        printf("\n");
    }
}

// Essa função só vai buscar a música na playlist
void buscarMusica(struct Musica **playlist, int numMusicas)
{
    // Solicitando ao usuário informações de busca
    char busca[50];
    printf("Digite o titulo ou artista da musica a ser buscada: ");
    scanf(" %[^\n]", busca);
    getchar(); // Limpando entrada

    printf("\nResultados da busca:\n");

    int encontrou = 0;
    for (int i = 0; i < numMusicas; i++)
    {
        // Verificando se as informações da música contém o termo de busca
        if (strstr((*playlist)[i].titulo, busca) || strstr((*playlist)[i].artista, busca))
        {
            printf("%d. %s - %s", i + 1, (*playlist)[i].titulo, (*playlist)[i].artista);
            if ((*playlist)[i].favorita)
            {
                printf(" (Favorita)");
            }
            printf("\n");
            encontrou = 1;
        }
    }
    if (!encontrou) // Verificando se nenhum resultado foi encontrado
    {
        printf("Nao foi possivel encontrar o termo \"%s\". Tente novamente !\n", busca);
    }
}

// Função que vai editar as informações das músicas
void editarMusica(struct Musica **playlist, int numMusicas)
{
    // Solicitando ao usuário o número da música a ser editada
    int indice = lerEntrada("Digite o numero da musica a ser editada: ");

    // Verificando se o número da música está dentro do intervalo válido
    if (indice >= 1 && indice <= numMusicas)
    {
        printf("Digite o novo titulo da musica: ");
        scanf(" %[^\n]", (*playlist)[indice - 1].titulo);
        getchar();

        printf("Digite o novo nome do artista: ");
        scanf(" %[^\n]", (*playlist)[indice - 1].artista);
        getchar();

        printf("Informacoes da musica foram editadas com sucesso !\n");
    }
    else if (indice != -1)
    {
        printf("Opcao invalida. Tente novamente !\n");
    }
}

// Exclui a música que o usuário quiser
void removerMusica(struct Musica **playlist, int *numMusicas)
{
    // Solicitando ao usuário o número da música a ser removida
    int indice = lerEntrada("Digite o numero da musica a ser removida: ");

    // Verificando se o índice está dentro do intervalo válido
    if (indice >= 1 && indice <= *numMusicas)
    {
        // Movendo todas as músicas uma posição para trás
        for (int i = indice - 1; i < *numMusicas - 1; i++)
        {
            (*playlist)[i] = (*playlist)[i + 1];
        }
        (*numMusicas)--;
        printf("Musica removida com sucesso !\n");
    }
    else if (indice != -1)
    {
        printf("Opcao invalida. Tente novamente !\n");
    }
}

// Função que vai favoritar as músicas
void favoritarMusica(struct Musica **playlist, int numMusicas)
{
    // Solicitando ao usuário o número da música a ser favoritada/desfavoritada
    int indice = lerEntrada("Digite o numero da musica a ser favoritada/desfavoritada: ");

    // Verificando se o índice está dentro do intervalo válido
    if (indice >= 1 && indice <= numMusicas)
    {
        // Alternando o status de favorito da música
        (*playlist)[indice - 1].favorita = !(*playlist)[indice - 1].favorita;

        // Verificando se a música é favorita
        if ((*playlist)[indice - 1].favorita)
        {
            printf("Musica favoritada com sucesso !\n");
        }
        else
        {
            printf("Musica desfavoritada com sucesso !\n");
        }
    }
    else if (indice != -1)
    {
        printf("Opcao invalida. Tente novamente !\n");
    }
}

// Parte difícil... salva a playlist na pasta output dentro de onde o arquivo todo está.
void salvarPlaylist(struct Musica **playlist, int numMusicas, char nomePessoa[])
{
    char nomeArquivo[100]; // Tamanho arbitrário para garantir espaço suficiente
    sprintf(nomeArquivo, "Playlist de %s.txt", nomePessoa);

    // Abrindo o arquivo para escrita
    FILE *arquivo = fopen(nomeArquivo, "w");

    // Verificando se o arquivo foi aberto com sucesso
    if (arquivo != NULL)
    {
        // Escrevendo o título da playlist no arquivo
        fprintf(arquivo, "Playlist de %s\n\n", nomePessoa);

        for (int i = 0; i < numMusicas; i++)
        {
            // Escrevendo as informações das músicas no arquivo
            fprintf(arquivo, "Música %d:\n", i + 1);
            fprintf(arquivo, "Título: %s\n", (*playlist)[i].titulo);
            fprintf(arquivo, "Artista: %s\n", (*playlist)[i].artista);
            if ((*playlist)[i].favorita)
            {
                fprintf(arquivo, "Status: Favorita\n\n");
            }
            else
            {
                fprintf(arquivo, "\n");
            }
        }

        fprintf(arquivo, "\nFim da Playlist.\n");

        // Fechando o arquivo
        fclose(arquivo);

        printf("Playlist salva com sucesso como \"%s\" com %d musicas !\n", nomeArquivo, numMusicas);
    }
    else
    {
        printf("Erro ao abrir o arquivo para salvar.\n");
    }
}