#include <stdio.h>         //fiz so esse comecinho do jeito que a gnt combinou pra ficar mais facil
#include <string.h>

#define MAX_MUSICAS 100
#define MAX_NOME 50

struct Musica {
    char titulo[50];
    char artista[50];
    int favorita;
};


//botei essa primeira parte de colocar musica na playlist,
// quem for revisar quando tiver completo avisa se deu bom la no grupo
void inserirMusica(struct Musica playlist[], int *numMusicas) {
    if (*numMusicas < MAX_MUSICAS) {
        struct Musica novaMusica;

        printf("Digite o titulo da musica: ");
        scanf(" %[^\n]", novaMusica.titulo);

        printf("Digite o nome do artista: ");
        scanf(" %[^\n]", novaMusica.artista);

        novaMusica.favorita = 0; // de comeco ela nao favorita ai tem que executar a outra funcao de favoritar, quem for fazer 
                                 // presta atenção aqui

        playlist[*numMusicas] = novaMusica;
        (*numMusicas)++;

        printf("Musica inserida com sucesso!\n");
    } else {
        printf("A playlist esta cheia. Remova musicas antes de adicionar novas.\n");
    }
}

//oiii gente, coloquei do jeito q a gtn combinou, minha parte de funcao, so pra mostrar msm!!
void mostrarPlaylist(struct Musica playlist[], int numMusicas) {
    printf("\nPlaylist:\n");
    for (int i = 0; i < numMusicas; i++) {
        printf("%d. %s - %s", i + 1, playlist[i].artista, playlist[i].titulo);
        if (playlist[i].favorita) {
            printf(" (Favoritada)");
        }
        printf("\n");
    }
}

//essa aqui so vai buscar a musica na playlist, p professor nao falou como, ai busca pelo nome e pelo autor
void buscarMusica(struct Musica playlist[], int numMusicas) {
    char busca[50];
    printf("Digite o titulo ou artista da musica a ser buscada: ");
    scanf(" %[^\n]", busca);

    printf("\nResultados da busca:\n");
    for (int i = 0; i < numMusicas; i++) {
        if (strstr(playlist[i].titulo, busca) || strstr(playlist[i].artista, busca)) {
            printf("%d. %s - %s", i + 1, playlist[i].artista, playlist[i].titulo);
            if (playlist[i].favorita) {
                printf(" (Favorita)");
            }
            printf("\n");
        }
    }
}

// Função que vai editar as informações das músicas
void editarMusica(struct Musica playlist[], int numMusicas) {
    
    int indice;
    printf("Digite o numero da musica a ser editada: ");
    scanf("%d", &indice);

    // Verifica se o número da música está dentro do intervalo válido
    if (indice >= 1 && indice <= numMusicas) {

        printf("Digite o novo titulo da musica: ");
        scanf(" %[^\n]", playlist[indice - 1].titulo);

        printf("Digite o novo nome do artista: ");
        scanf(" %[^\n]", playlist[indice - 1].artista);
      
        printf("Informações da musica editadas com sucesso!\n");
    } else {
        printf("Numero invalido.\n");
    }
}
//Exclui a musica que quiser
void removerMusica(struct Musica playlist[], int *numMusicas) {
    int indice;
    printf("Digite o numero da musica a ser removida: ");
    scanf("%d", &indice);

    if (indice >= 1 && indice <= *numMusicas) {
        for (int i = indice - 1; i < *numMusicas - 1; i++) {
            playlist[i] = playlist[i + 1];
        }
        (*numMusicas)--;
        printf("Musica removida com sucesso!\n");
    } else {
        printf("Numero invalido.\n");
    }
}

//Talvez favorite a musica, tem que testar :(
void favoritarMusica(struct Musica playlist[], int numMusicas) {
    int indice;
    printf("Digite o numero da musica a ser favoritada/desfavoritada: ");
    scanf("%d", &indice);

    if (indice >= 1 && indice <= numMusicas) {
        playlist[indice - 1].favorita = !playlist[indice - 1].favorita;
        if (playlist[indice - 1].favorita) {
            printf("Musica favoritada com sucesso!\n");
        } else {
            printf("Musica desfavoritada com sucesso!\n");
        }
    } else {
        printf("Numero invalido.\n");
    }
}

// Parte dificil... salva a playlist na pasta output dentro de onde o arquivo todo ta, demorei mas achei onde salva
void salvarPlaylist(struct Musica playlist[], int numMusicas, char nomePessoa[]) {
    char nomeArquivo[100];  // Tamanho arbitrário para garantir espaço suficiente
    sprintf(nomeArquivo, "Playlist de %s.txt", nomePessoa);

    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo != NULL) {
        for (int i = 0; i < numMusicas; i++) {
            fprintf(arquivo, "%s - %s - %d\n", playlist[i].titulo, playlist[i].artista, playlist[i].favorita);
        }

        fclose(arquivo);

        printf("Playlist salva com sucesso como \"%s\"!\n", nomeArquivo);
    } else {
        printf("Erro ao abrir o arquivo para salvar.\n");
    }
}
// so juntei tudo e tentei incluir tudo, acho que foi.
int main() {
    struct Musica playlist[MAX_MUSICAS];
    int numMusicas = 0;
    int opcao;

    char nomePessoa[MAX_NOME];

    printf("Digite o seu nome: ");
    scanf(" %[^\n]", nomePessoa);

    do {
         printf("\n=== MENU ===\n");
        printf("1. Inserir nova musica\n");
        printf("2. Mostrar musicas cadastradas\n");
        printf("3. Buscar por uma musica\n");
        printf("4. Editar informacoes de uma musica \n");
        printf("5. Remover musica\n");
        printf("6. Favoritar/Desfavoritar musica\n");
        printf("7. Salvar playlist em um arquivo\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");



        scanf("%d", &opcao);

        switch (opcao) {
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
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 8);

    return 0;
}