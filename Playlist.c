#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include "interface.h"

// Só juntei tudo na função main
int main()
{
    int tamanhoPlaylist = 10; // Começamos com espaço para 10 músicas
    struct Musica *playlist = malloc(tamanhoPlaylist * sizeof(struct Musica));

    // Verificando se a memória foi alocada com sucesso
    if (playlist == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    int numMusicas = 0;
    int opcao;
    char nomePessoa[50];

    // Solicitando ao usuário o nome
    printf("Digite o seu nome: ");
    scanf(" %[^\n]", nomePessoa);
    getchar(); // Limpando entrada

    do
    {
        imprimirMenu(); // Imprimindo o menu
        opcao = lerEntrada(""); // Lendo a entrada do usuário

        // Executando a opção escolhida pelo usuário
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
            printf("Saindo do programa. Ate mais !\n");
            break;
        case -1:
            // Não faz nada
            break;
        default:
            printf("Opcao invalida. Tente novamente !\n");
        }
    } while (opcao != 8);

    free(playlist); // Liberando memória

    return 0;
}