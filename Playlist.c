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
