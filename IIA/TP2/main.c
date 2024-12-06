#include <stdio.h>
#include <stdlib.h>

void ler_arquivo(const char *caminho_arquivo, float *objetivo, float *moedas, int *num_moedas){
    FILE *arquivo = fopen(caminho_arquivo, "r");

    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo %s\n", caminho_arquivo);
        exit(1);
    }

    // Ler a primeira linha (número de moedas e objetivo)
    fscanf(arquivo, "%d %f", num_moedas, objetivo);

    // Ler a segunda linha (valores das moedas)
    for (int i = 0; i < *num_moedas; i++){
        fscanf(arquivo, "%f", &moedas[i]);
    }

    fclose(arquivo);
}

int main(){
    const char *caminho = "file1.txt"; 
    float objetivo;
    int num_moedas;
    float moedas[10]; // Supondo um máximo de 10 moedas (ajuste conforme necessário)

    ler_arquivo(caminho, &objetivo, moedas, &num_moedas);

    printf("Objetivo: %.2f\n", objetivo);
    printf("Moedas: ");
    for (int i = 0; i < num_moedas; i++){
        printf("%.2f ", moedas[i]);
    }
    printf("\n");

    return 0;
}
