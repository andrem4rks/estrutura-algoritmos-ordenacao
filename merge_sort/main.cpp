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

void intercala (int *v, int inicio, int meio, int fim) {
    int prim, seg, k, *w;
    w = (int*)malloc ((fim-inicio+1) * sizeof (int));

    prim = inicio; seg = meio+1; k = 0;
    while (prim <= meio && seg <= fim) {
        if (v[prim] <= v[seg])
            w[k++] = v[prim++];
        else w[k++] = v[seg++];
    }
    while (prim <= meio)
        w[k++] = v[prim++];
    while (seg <= fim)
        w[k++] = v[seg++];
    for (prim = inicio; prim <= fim; prim++)
        v[prim] = w[prim-inicio];
    free (w);
}


void merge_sort (int *v, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim)/2;
        merge_sort (v, inicio, meio);
        merge_sort (v, meio+1, fim);
        intercala (v, inicio, meio, fim);
    }
}

int main() {
    int *numeros;

    FILE *arq;

    arq = fopen("mergesort.txt", "wt");


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
                merge_sort(numeros, 0, j);
                auto fim = steady_clock::now();
                auto tempo = fim - inicio;
                fprintf(arq, "%d %lf\n", j, (tempo).count() / 1000000.0);
                delete[] numeros;
            } else if (i == 1 || j / (10 * multiplicador) != 1) {
                numeros = gera_vetor(numeros, j);
                auto inicio = steady_clock::now();
                merge_sort(numeros, 0, j);
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
