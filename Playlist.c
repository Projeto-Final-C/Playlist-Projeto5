// fiz só esse comecinho do jeito que a gnt combinou pra ficar mais fácil
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Musica
{
    char titulo[50];
    char artista[50];
    int favorita;
} Musica;

// Botei essa primeira parte de colocar música na playlist,
// Agora a playlist é um ponteiro
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

    printf("Digite o titulo da musica: ");
    scanf(" %[^\n]", novaMusica.titulo);

    printf("Digite o nome do artista: ");
    scanf(" %[^\n]", novaMusica.artista);

    novaMusica.favorita = 0;

    (*playlist)[*numMusicas] = novaMusica;
    (*numMusicas)++;

    printf("Musica inserida com sucesso!\n");
}

// oiii gente, coloquei do jeito que a gnt combinou, minha parte de função, só pra mostrar msm!!
void mostrarPlaylist(struct Musica **playlist, int numMusicas)
{
    printf("\nPlaylist:\n");
    for (int i = 0; i < numMusicas; i++)
    {
        printf("%d. %s - %s", i + 1, (*playlist)[i].artista, (*playlist)[i].titulo);
        if ((*playlist)[i].favorita)
        {
            printf(" (Favoritada)");
        }
        printf("\n");
    }
}

// Essa aqui só vai buscar a música na playlist.
void buscarMusica(struct Musica **playlist, int numMusicas)
{
    char busca[50];
    printf("Digite o titulo ou artista da musica a ser buscada: ");
    scanf(" %[^\n]", busca);

    printf("\nResultados da busca:\n");
    for (int i = 0; i < numMusicas; i++)
    {
        if (strstr((*playlist)[i].titulo, busca) || strstr((*playlist)[i].artista, busca))
        {
            printf("%d. %s - %s", i + 1, (*playlist)[i].artista, (*playlist)[i].titulo);
            if ((*playlist)[i].favorita)
            {
                printf(" (Favorita)");
            }
            printf("\n");
        }
    }
}

// Função que vai editar as informações das músicas
void editarMusica(struct Musica **playlist, int numMusicas)
{

    int indice;
    printf("Digite o numero da musica a ser editada: ");
    scanf("%d", &indice);

    // Verifica se o número da música está dentro do intervalo válido
    if (indice >= 1 && indice <= numMusicas)
    {

        printf("Digite o novo titulo da musica: ");
        scanf(" %[^\n]", (*playlist)[indice - 1].titulo);

        printf("Digite o novo nome do artista: ");
        scanf(" %[^\n]", (*playlist)[indice - 1].artista);

        printf("Informacoes da musica editadas com sucesso!\n");
    }
    else
    {
        printf("Numero invalido. Tente novamente.\n");
    }
}

// Exclui a música que quiser
void removerMusica(struct Musica **playlist, int *numMusicas)
{
    int indice;
    printf("Digite o numero da musica a ser removida: ");
    scanf("%d", &indice);

    if (indice >= 1 && indice <= *numMusicas)
    {
        for (int i = indice - 1; i < *numMusicas - 1; i++)
        {
            (*playlist)[i] = (*playlist)[i + 1];
        }
        (*numMusicas)--;
        printf("Musica removida com sucesso!\n");
    }
    else
    {
        printf("Numero invalido. Tente novamente.\n");
    }
}

// Função que vai favoritar as músicas
void favoritarMusica(struct Musica **playlist, int numMusicas)
{
    int indice;
    printf("Digite o numero da musica a ser favoritada/desfavoritada: ");
    scanf("%d", &indice);

    if (indice >= 1 && indice <= numMusicas)
    {
        (*playlist)[indice - 1].favorita = !(*playlist)[indice - 1].favorita;
        if ((*playlist)[indice - 1].favorita)
        {
            printf("Musica favoritada com sucesso!\n");
        }
        else
        {
            printf("Musica desfavoritada com sucesso!\n");
        }
    }
    else
    {
        printf("Numero invalido. Tente novamente.\n");
    }
}

// Parte difícil... salva a playlist na pasta output dentro de onde o arquivo todo ta.
void salvarPlaylist(struct Musica **playlist, int numMusicas, char nomePessoa[])
{
    char nomeArquivo[100]; // Tamanho arbitrário para garantir espaço suficiente
    sprintf(nomeArquivo, "Playlist de %s.txt", nomePessoa);

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo != NULL)
    {
        for (int i = 0; i < numMusicas; i++)
        {
            fprintf(arquivo, "%s - %s - %d\n", (*playlist)[i].titulo, (*playlist)[i].artista, (*playlist)[i].favorita);
        }

        fclose(arquivo);

        printf("Playlist salva com sucesso como \"%s\"!\n", nomeArquivo);
    }
    else
    {
        printf("Erro ao abrir o arquivo para salvar.\n");
    }
}

// Só juntei tudo e tentei incluir tudo.
int main()
{
    int tamanhoPlaylist = 10; // Começamos com espaço para 10 músicas
    
    struct Musica *playlist = malloc(tamanhoPlaylist * sizeof(struct Musica));
    if (playlist == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    int numMusicas = 0;
    int opcao;

    char nomePessoa[50];

    printf("Digite o seu nome: ");
    scanf(" %[^\n]", nomePessoa);

    do
    {
        printf("\n+--------------------------+\n");
        printf("|           MENU           |\n");
        printf("+--------------------------+\n");
        printf("| 1. Inserir nova musica   |\n");
        printf("| 2. Mostrar musicas       |\n");
        printf("| 3. Buscar musica         |\n");
        printf("| 4. Editar musica         |\n");
        printf("| 5. Remover musica        |\n");
        printf("| 6. Favoritar musica      |\n");
        printf("| 7. Salvar playlist       |\n");
        printf("| 8. Sair                  |\n");
        printf("+--------------------------+\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            inserirMusica(&playlist, &numMusicas, &tamanhoPlaylist);
            break;
        case 2:
            mostrarPlaylist(&playlist, numMusicas);
            break;
        case 3:
            buscarMusica(&playlist, numMusicas);
            break;
        case 4:
            editarMusica(&playlist, numMusicas);
            break;
        case 5:
            removerMusica(&playlist, &numMusicas);
            break;
        case 6:
            favoritarMusica(&playlist, numMusicas);
            break;
        case 7:
            salvarPlaylist(&playlist, numMusicas, nomePessoa);
            break;
        case 8:
            printf("Saindo do programa. Ate mais!\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 8);

    free(playlist); // Liberando memória

    return 0;
}