#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Estruturas para representar grafos, arestas e subgrafos
struct Aresta {
    int origem, destino, peso;
};

struct Grafo {
    int V, A; 
    struct Aresta* arestas;
};

struct SubGrafo {
    int procura;
    int raiz;
};


//esta função é responsável por criar o grafo
struct Grafo* criarGrafo(int V, int A) {
    struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    grafo->V = V;
    grafo->A = A;
    grafo->arestas = (struct Aresta*)malloc(A * sizeof(struct Aresta));
    return grafo;
}

// Contadores para as operacoes
long long int operacao_find = 0; // Contador para find
long long int operacao_union = 0; // Contador para union

//Esta função usa o algoritmo de compressao de caminhos para encontrar a raiz de um subgrafo
int find(struct SubGrafo* subgrafo, int i) {
    operacao_find++;
    if (subgrafo[i].procura != i) {
        subgrafo[i].procura = find(subgrafo, subgrafo[i].procura);
    }
    return subgrafo[i].procura;
}

//Esta função tem como objetivo juntar dois subgrafos
void unionSet(struct SubGrafo* subgrafo, int x, int y) {
    operacao_union++;
    int xraiz = find(subgrafo, x);
    int yraiz = find(subgrafo, y);
    
   if (xraiz != yraiz) {
        if (subgrafo[xraiz].raiz < subgrafo[yraiz].raiz) {
            subgrafo[xraiz].procura = yraiz;
        } else if (subgrafo[xraiz].raiz > subgrafo[yraiz].raiz) {
            subgrafo[yraiz].procura = xraiz;
        } else {
            subgrafo[yraiz].procura = xraiz;
            subgrafo[xraiz].raiz++;
        }
    }
}

// Esta função compara duas arestas levando em conta o peso
int compararArestas(const void* a, const void* b) {
    return ((struct Aresta*)a)->peso - ((struct Aresta*)b)->peso;
}

// Algoritmo de Kruskal 
void kruskal(struct Grafo* grafo) {
    int V = grafo->V;
    struct Aresta* resultado = (struct Aresta*)malloc((V - 1) * sizeof(struct Aresta));
    int e = 0; 
    int i = 0; 
    int custoTotal = 0;

    struct SubGrafo* subgrafo = (struct SubGrafo*)malloc(V * sizeof(struct SubGrafo));
    for (int v = 0; v < V; ++v) {
        subgrafo[v].procura = v;
        subgrafo[v].raiz = 0;
    }

    // Utilizamos qsort para ordenar as arestas por peso
    qsort(grafo->arestas, grafo->A, sizeof(grafo->arestas[0]),compararArestas);

    while (e < V - 1 && i < grafo->A) {
        struct Aresta proximaAresta = grafo->arestas[i++];
        
        int x = find(subgrafo, proximaAresta.origem);
        int y = find(subgrafo, proximaAresta.destino);

        if (x != y) {
            resultado[e++] = proximaAresta;
            unionSet(subgrafo, x, y);
            custoTotal += proximaAresta.peso;
        }
    }

    // Verificação de corretude
if (e == grafo->V - 1) {
    printf("A MST gerada está correta.\n");
} else {
    printf("Erro: MST incorreta! Arestas na MST: %d, esperado: %d\n", e, grafo->V - 1);
}

// Impressão das arestas da MST
printf("Arestas do MST:\n");
for (i = 0; i < e; ++i) {
    printf("%d -- %d == %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
}

    printf("Custo total do MST: %d\n", custoTotal);

    // meio encontrado para calcular o uso de memoria
    long long int memoria = 0;
    memoria += grafo->A * sizeof(struct Aresta); 
    memoria += grafo->V * sizeof(struct SubGrafo);
    printf("Uso de memoria: %lld bytes\n", memoria);

    free(subgrafo);
    free(resultado);
}

int main() {
    clock_t inicio, fim;
    double tempoGasto;
    int V, A;
    operacao_find = 0;
    operacao_union = 0; 
    printf("Informe o numero de vertices do grafo: ");
    scanf("%d", &V);
    
    printf("Informe o numero de arestas do grafo: ");
    scanf("%d", &A);
    
    struct Grafo* grafo = criarGrafo(V, A);
    
    printf("Informe as arestas no formato 'origem destino peso':\n");
    for (int i = 0; i < A; i++) {
        printf("Aresta %d: ", i);
        scanf("%d %d %d", &grafo->arestas[i].origem, &grafo->arestas[i].destino, &grafo->arestas[i].peso);
    }

    inicio = clock();
    kruskal(grafo);
    fim = clock();

    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto: %.2f segundos\n", tempoGasto);
    printf("O numero de peracoes find foi: %lld\n", operacao_find);
    printf("O numero de operacoes union  foi: %lld\n", operacao_union);

    free(grafo->arestas);
    free(grafo);
    
    return 0;
}
