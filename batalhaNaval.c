//Criado por Alexssandro de Souza Freitas.
//Versão 1.0

#include <stdio.h>

#define TAM 10

void imprimirTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void aplicarPadrao(int tab[TAM][TAM], int linha, int coluna, int padrao[3][5]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            int x = linha + i;
            int y = coluna + j - 2;
            if (x >= 0 && x < TAM && y >= 0 && y < TAM && padrao[i][j] == 1) {
                tab[x][y] = 1;
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};    // 0 = vazio, 3 = navio
    int ataques[TAM][TAM] = {0};      // 0 = não atacado, 1 = atacado
    int acertos[TAM][TAM] = {0};      // 0 = não acertou navio, 1 = acertou navio

    // Posicionar navios (igual antes)
    for (int i = 1; i <= 5; i++) tabuleiro[i][2] = 3;
    for (int j = 4; j <= 7; j++) tabuleiro[7][j] = 3;
    for (int k = 0; k < 3; k++) tabuleiro[k][k] = 3;
    for (int k = 0; k < 4; k++) tabuleiro[6 + k][9 - k] = 3;

    int cone[3][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1}
    };
    int octaedro[3][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };
    int cruz[3][5] = {
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0}
    };

    printf("Tabuleiro inicial com navios (3 = navio):\n");
    imprimirTabuleiro(tabuleiro);

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        printf("Escolha a habilidade para atacar:\n");
        printf("1 - Cone\n2 - Octaedro\n3 - Cruz\nOpcao: ");
        int opcao;
        scanf("%d", &opcao);

        int linha, coluna;
        printf("Digite a linha (0 a 9) para aplicar a habilidade: ");
        scanf("%d", &linha);
        printf("Digite a coluna (0 a 9) para aplicar a habilidade: ");
        scanf("%d", &coluna);

        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            printf("Posicao invalida!\n");
            continue;
        }

        // Aplicar habilidade escolhida
        switch (opcao) {
            case 1: aplicarPadrao(ataques, linha, coluna, cone); break;
            case 2: aplicarPadrao(ataques, linha, coluna, octaedro); break;
            case 3: aplicarPadrao(ataques, linha, coluna, cruz); break;
            default:
                printf("Opcao invalida!\n");
                continue;
        }

        // Verificar acertos (ataque = 1 e navio = 3)
        for (int i = 0; i < TAM; i++) {
            for (int j = 0; j < TAM; j++) {
                if (ataques[i][j] == 1 && tabuleiro[i][j] == 3) {
                    acertos[i][j] = 1;
                }
            }
        }

        printf("Tabuleiro de ataques (1 = area atacada):\n");
        imprimirTabuleiro(ataques);

        printf("Tabuleiro de acertos (1 = navio atingido):\n");
        imprimirTabuleiro(acertos);

        printf("Deseja atacar novamente? (s/n): ");
        scanf(" %c", &continuar);
    }

    printf("Jogo finalizado!\n");
    return 0;
}
