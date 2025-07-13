#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//nó de adjacência
typedef struct Adj {
    int vertice;
    int peso;
    struct Adj* prox;
} Adj;

//grafo com listas de adjacência
typedef struct {
    Adj** inicio;
    int numVertices;
} Grafo;

//representa uma aresta
typedef struct {
    int origem, destino, peso;
} Aresta;

// Subgrafo para Union-Find
typedef struct {
    int procura;
    int raiz;
} SubGrafo;

// Contadores
long long int operacao_find = 0;
long long int operacao_union = 0;

// listas de adjacência
Adj* novoAdj(int v, int peso) {
    Adj* novo = malloc(sizeof(Adj));
    novo->vertice = v;
    novo->peso = peso;
    novo->prox = NULL;
    return novo;
}

void inicializaGrafo(Grafo* g, int n) {
    g->numVertices = n;
    g->inicio = malloc(n * sizeof(Adj*));
    for (int i = 0; i < n; i++)
        g->inicio[i] = NULL;
}

void adicionaAresta(Grafo* g, int u, int v, int peso) {
    Adj* novo = novoAdj(v, peso);
    novo->prox = g->inicio[u];
    g->inicio[u] = novo;

    novo = novoAdj(u, peso); 
    novo->prox = g->inicio[v];
    g->inicio[v] = novo;
}

void liberaGrafo(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        Adj* atual = g->inicio[i];
        while (atual) {
            Adj* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->inicio);
}

//Union-Find com contadores
int find(SubGrafo* subgrafo, int i) {
    operacao_find++;
    if (subgrafo[i].procura != i)
        subgrafo[i].procura = find(subgrafo, subgrafo[i].procura);
    return subgrafo[i].procura;
}

void unionSet(SubGrafo* subgrafo, int x, int y) {
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

// Comparador para qsort
int compararArestas(const void* a, const void* b) {
    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

// Algoritmo de Kruskal
void kruskal(Grafo* g, Aresta* arestas, int A) {
    int V = g->numVertices;
    Aresta* resultado = malloc((V - 1) * sizeof(Aresta));
    int e = 0, i = 0, custoTotal = 0;

    SubGrafo* subgrafo = malloc(V * sizeof(SubGrafo));
    for (int v = 0; v < V; v++) {
        subgrafo[v].procura = v;
        subgrafo[v].raiz = 0;
    }

    qsort(arestas, A, sizeof(Aresta), compararArestas);

    while (e < V - 1 && i < A) {
        Aresta proxima = arestas[i++];
        int x = find(subgrafo, proxima.origem);
        int y = find(subgrafo, proxima.destino);
        if (x != y) {
            resultado[e++] = proxima;
            unionSet(subgrafo, x, y);
            custoTotal += proxima.peso;
        }
    }

    if (e == V - 1) {
        printf("A MST gerada está correta.\n");
    } else {
        printf("Erro: MST incorreta! Arestas na MST: %d, esperado: %d\n", e, V - 1);
    }

    printf("Arestas da MST:\n");
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", resultado[i].origem, resultado[i].destino, resultado[i].peso);
    }

    printf("Custo total do MST: %d\n", custoTotal);

    // Estimativa de memória
    long long int memoria = 0;
    memoria += V * sizeof(SubGrafo);
    memoria += A * sizeof(Aresta);
    printf("Uso de memoria: %lld bytes\n", memoria);

    free(subgrafo);
    free(resultado);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_grafo.txt>\n", argv[0]);
        return 1;
    }

    FILE* arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    int V, A;
    fscanf(arquivo, "%d %d", &V, &A);

    Grafo g;
    inicializaGrafo(&g, V);

    Aresta* arestas = malloc(A * sizeof(Aresta));

    for (int i = 0; i < A; i++) {
        int u, v, peso;
        fscanf(arquivo, "%d %d %d", &u, &v, &peso);
        adicionaAresta(&g, u, v, peso);
        arestas[i].origem = u;
        arestas[i].destino = v;
        arestas[i].peso = peso;
    }
    fclose(arquivo);

    clock_t inicio = clock();
    kruskal(&g, arestas, A);
    clock_t fim = clock();

    printf("Tempo gasto: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Operacoes find: %lld\n", operacao_find);
    printf("Operacoes union: %lld\n", operacao_union);

    free(arestas);
    liberaGrafo(&g);
    return 0;
}
