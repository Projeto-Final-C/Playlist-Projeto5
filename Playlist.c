#include <stdio.h> //fiz só esse comecinho do jeito que a gnt combinou pra ficar mais fácil
#include <string.h>

#define MAX_MUSICAS 100
#define MAX_NOME 50

typedef struct Musica
{
    char titulo[50];
    char artista[50];
    int favorita;
} Musica;

// Botei essa primeira parte de colocar música na playlist,
// Quem for revisar quando tiver completo avisa se deu bom lá no grupo
void inserirMusica(Musica playlist[], int *numMusicas)
{
    if (*numMusicas < MAX_MUSICAS)
    {
        Musica novaMusica;

        printf("Digite o titulo da musica: ");
        scanf(" %[^\n]", novaMusica.titulo);

        printf("Digite o nome do artista: ");
        scanf(" %[^\n]", novaMusica.artista);

        novaMusica.favorita = 0; // De começo ela não favorita aí tem que executar a outra função de favoritar, quem for fazer.
                                            // Presta atenção aqui !!!

        playlist[*numMusicas] = novaMusica;
        (*numMusicas)++;

        printf("Musica inserida com sucesso!\n");
    }
    else
    {
        printf("A playlist esta cheia. Remova musicas antes de adicionar novas.\n");
    }
}

// oiii gente, coloquei do jeito que a gnt combinou, minha parte de função, só pra mostrar msm!!
void mostrarPlaylist(Musica playlist[], int numMusicas)
{
    printf("\nPlaylist:\n");
    for (int i = 0; i < numMusicas; i++)
    {
        printf("%d. %s - %s", i + 1, playlist[i].artista, playlist[i].titulo);
        if (playlist[i].favorita)
        {
            printf(" (Favoritada)");
        }
        printf("\n");
    }
}

// Essa aqui só vai buscar a música na playlist, o professor não falou como, aí busca pelo nome e pelo autor
void buscarMusica(Musica playlist[], int numMusicas)
{
    char busca[50];
    printf("Digite o titulo ou artista da musica a ser buscada: ");
    scanf(" %[^\n]", busca);

    printf("\nResultados da busca:\n");
    for (int i = 0; i < numMusicas; i++)
    {
        if (strstr(playlist[i].titulo, busca) || strstr(playlist[i].artista, busca))
        {
            printf("%d. %s - %s", i + 1, playlist[i].artista, playlist[i].titulo);
            if (playlist[i].favorita)
            {
                printf(" (Favorita)");
            }
            printf("\n");
        }
    }
}

// Função que vai editar as informações das músicas
void editarMusica(Musica playlist[], int numMusicas)
{
    int indice;
    printf("Digite o numero da musica a ser editada: ");
    scanf("%d", &indice);

    // Verifica se o número da música está dentro do intervalo válido
    if (indice >= 1 && indice <= numMusicas)
    {

        printf("Digite o novo titulo da musica: ");
        scanf(" %[^\n]", playlist[indice - 1].titulo);

        printf("Digite o novo nome do artista: ");
        scanf(" %[^\n]", playlist[indice - 1].artista);

        printf("Informacoes da musica editadas com sucesso!\n");
    }
    else
    {
        printf("Numero invalido.\n");
    }
}

// Exclui a música que quiser
void removerMusica(Musica playlist[], int *numMusicas)
{
    int indice;
    printf("Digite o numero da musica a ser removida: ");
    scanf("%d", &indice);

    if (indice >= 1 && indice <= *numMusicas)
    {
        for (int i = indice - 1; i < *numMusicas - 1; i++)
        {
            playlist[i] = playlist[i + 1];
        }
        (*numMusicas)--;
        printf("Musica removida com sucesso!\n");
    }
    else
    {
        printf("Numero invalido.\n");
    }
}

// Talvez favorite a música, tem que testar :(
void favoritarMusica(Musica playlist[], int numMusicas)
{
    int indice;
    printf("Digite o numero da musica a ser favoritada/desfavoritada: ");
    scanf("%d", &indice);

    if (indice >= 1 && indice <= numMusicas)
    {
        playlist[indice - 1].favorita = !playlist[indice - 1].favorita;
        if (playlist[indice - 1].favorita)
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
        printf("Numero invalido.\n");
    }
}

// Parte difícil... salva a playlist na pasta output dentro de onde o arquivo todo ta, demorei mas achei onde salva
void salvarPlaylist(Musica playlist[], int numMusicas, char nomePessoa[])
{
    char nomeArquivo[100]; // Tamanho arbitrário para garantir espaço suficiente
    sprintf(nomeArquivo, "Playlist de %s.txt", nomePessoa);

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo != NULL)
    {
        for (int i = 0; i < numMusicas; i++)
        {
            fprintf(arquivo, "%s - %s - %d\n", playlist[i].titulo, playlist[i].artista, playlist[i].favorita);
        }

        fclose(arquivo);

        printf("Playlist salva com sucesso como \"%s\"!\n", nomeArquivo);
    }
    else
    {
        printf("Erro ao abrir o arquivo para salvar.\n");
    }
}

// Só juntei tudo e tentei incluir tudo, acho que foi.
int main()
{
    Musica playlist[MAX_MUSICAS];
    int numMusicas = 0;
    int opcao;

    char nomePessoa[MAX_NOME];

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
            inserirMusica(playlist, &numMusicas);
            break;
        case 2:
            mostrarPlaylist(playlist, numMusicas);
            break;
        case 3:
            buscarMusica(playlist, numMusicas);
            break;
        case 4:
            editarMusica(playlist, numMusicas);
            break;
        case 5:
            removerMusica(playlist, &numMusicas);
            break;
        case 6:
            favoritarMusica(playlist, numMusicas);
            break;
        case 7:
            salvarPlaylist(playlist, numMusicas, nomePessoa);
            break;
        case 8:
            printf("Saindo do programa. Ate mais!\n");

            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 8);

    return 0;
}