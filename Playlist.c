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