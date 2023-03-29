#include <iostream>
#include <stdio.h>
#include <chrono>
#include <vector>
#include <random>
#include <string.h>

using namespace std;
using namespace std::chrono;

int *gera_vetor(int *numeros, int tam) {
    std::random_device rd;
    std::mt19937_64 gen{rd()};
    std::uniform_int_distribution<int> dist{0, tam};
    numeros = new int[tam];
    for (int i = 0; i < tam; i++) {
        numeros[i] = dist(gen);
    }
    return numeros;
}

void selection_sort(int *numeros, int tam) {
    int i, j, min, aux;

    for (i = 0; i < (tam - 1); i++) {
        min = i;
        for (j = i + 1; j < tam; j++) {
            if (numeros[j] < numeros[min]) {
                min = j;
            }
        }
        if (i != min) {
            aux = numeros[i];
            numeros[i] = numeros[min];
            numeros[min] = aux;
        }
    }
}

int main() {
    int *numeros;

    FILE *arq;

    arq = fopen("selectionsort.txt", "wt");


    if (arq == NULL) {
        printf("PROBLEMAS AO ABRIR ARQUIVO!");
        return 0;
    }

    int multiplicador = 1;
    fprintf(arq, "n tempo\n\n");
    for (int i = 1; i <= 5; i++) {
        if (i > 1) {
            fprintf(arq, "// o tamanho do vetor varia de %d em %d\n", multiplicador * 10, multiplicador * 10);
        }
        for (int j = 10 * multiplicador; j <= 100 * multiplicador; j += 10 * multiplicador) {
            if (i == 1) {
                numeros = gera_vetor(numeros, j);
                auto inicio = steady_clock::now();
                selection_sort(numeros, j);
                auto fim = steady_clock::now();
                auto tempo = fim - inicio;
                fprintf(arq, "%d %lf\n", j, (tempo).count() / 1000000.0);
                delete[] numeros;
            } else if (i == 1 || j / (10 * multiplicador) != 1) {
                numeros = gera_vetor(numeros, j);
                auto inicio = steady_clock::now();
                selection_sort(numeros, j);
                auto fim = steady_clock::now();
                auto tempo = fim - inicio;
                fprintf(arq, "%d %lf\n", j, (tempo).count() / 1000000.0); // devolve o tempo em nanosegundos
                delete[] numeros;
            }
        }
        multiplicador *= 10;
    }
    fclose(arq);


    return 0;
}
