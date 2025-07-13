#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Estrutura de um nó na lista de adjacência
typedef struct Adj {
    int vertice;        
    int peso;             
    struct Adj* prox;   
} Adj;

// Estrutura do grafo com listas de adjacência
typedef struct {
    Adj** inicio; 
    int numVertices;          
} Grafo;

// Estrutura para representar um nó no heap mínimo
typedef struct {
    int vertice;   
    int chave;     
} HeapNode;

// Estrutura de um heap mínimo
typedef struct {
    HeapNode** vetor; 
    int* pos;          
    int tamanho;                   
} MinHeap;

// Cria um novo nó de adjacência
Adj* novoAdj(int v, int peso) {
    Adj* novo = malloc(sizeof(Adj));
    novo->vertice = v;
    novo->peso = peso;
    novo->prox = NULL;
    return novo;
}

// Inicializa um grafo vazio com 'n' vértices
void inicializaGrafo(Grafo* g, int n) {
    g->numVertices = n;
    g->inicio = malloc(n * sizeof(Adj*)); 
    for (int i = 0; i < n; i++) {
        g->inicio[i] = NULL;
    }
}

// Adiciona uma aresta bidirecional ao grafo
void adicionaAresta(Grafo* g, int u, int v, int peso) {
    Adj* novo = novoAdj(v, peso);
    novo->prox = g->inicio[u];
    g->inicio[u] = novo;

    novo = novoAdj(u, peso);
    novo->prox = g->inicio[v];
    g->inicio[v] = novo;
}

// Libera toda a memória alocada para o grafo
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

// Contadores para as operacoes
int contadorExtraiMin = 0;
int contadorDiminuiChave = 0;

// Cria e inicializa uma heap mínima
MinHeap* criaMinHeap(int capacidade) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->vetor = malloc(capacidade * sizeof(HeapNode*));
    heap->pos = malloc(capacidade * sizeof(int));
    heap->tamanho = 0;
    for (int i = 0; i < capacidade; i++) {
        heap->vetor[i] = NULL;
        heap->pos[i] = -1;
    }
    return heap;
}

// Libera a memória alocada para o heap
void liberaMinHeap(MinHeap* heap, int n) {
    free(heap->vetor);
    free(heap->pos); 
    free(heap);
}

// Troca dois ponteiros de HeapNode
void troca(HeapNode** a, HeapNode** b) {
    HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Mantém a propriedade de heap mínimo recursivamente
void minHeapify(MinHeap* heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && heap->vetor[esq]->chave < heap->vetor[menor]->chave)
        menor = esq;
    if (dir < heap->tamanho && heap->vetor[dir]->chave < heap->vetor[menor]->chave)
        menor = dir;

    if (menor != idx) {
        heap->pos[heap->vetor[menor]->vertice] = idx;
        heap->pos[heap->vetor[idx]->vertice] = menor;
        troca(&heap->vetor[menor], &heap->vetor[idx]);
        minHeapify(heap, menor);
    }
}

// Verifica se um vértice ainda está no heap
int estaNoHeap(MinHeap* heap, int v) {
    return heap->pos[v] != -1;
}

// Extrai o nó com menor chave do heap
HeapNode* extraiMin(MinHeap* heap) {
    if (heap->tamanho == 0) return NULL;

    HeapNode* raiz = heap->vetor[0];
    HeapNode* ultimo = heap->vetor[--heap->tamanho];
    heap->vetor[0] = ultimo;
    heap->pos[raiz->vertice] = -1;
    heap->pos[ultimo->vertice] = 0;
    minHeapify(heap, 0);
    return raiz;
}

// Atualiza o valor da chave de um vértice e ajusta o heap
void diminuiChave(MinHeap* heap, int v, int chave) {
    int i = heap->pos[v];
    heap->vetor[i]->chave = chave;

    while (i && heap->vetor[i]->chave < heap->vetor[(i - 1) / 2]->chave) {
        heap->pos[heap->vetor[i]->vertice] = (i - 1) / 2;
        heap->pos[heap->vetor[(i - 1) / 2]->vertice] = i;
        troca(&heap->vetor[i], &heap->vetor[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Algoritmo de Prim
void prim(Grafo* g) {
    int* pai = malloc(g->numVertices * sizeof(int));      
    int* chave = malloc(g->numVertices * sizeof(int));    
    MinHeap* heap = criaMinHeap(g->numVertices);          

    // Inicialização
    for (int v = 0; v < g->numVertices; v++) {
        pai[v] = -1;
        chave[v] = INT_MAX;
        heap->vetor[v] = malloc(sizeof(HeapNode));
        heap->vetor[v]->vertice = v;
        heap->vetor[v]->chave = INT_MAX;
        heap->pos[v] = v;
    }

    // Começa pelo vértice 0
    chave[0] = 0;
    heap->vetor[0]->chave = 0;
    heap->tamanho = g->numVertices;

    // Loop principal do algoritmo
    while (heap->tamanho > 0) {
        HeapNode* min = extraiMin(heap);
        contadorExtraiMin++;  // Contabiliza extraiMin
        int u = min->vertice;

        // Percorre os vizinhos de u
        Adj* atual = g->inicio[u];
        while (atual) {
            int v = atual->vertice;
            if (estaNoHeap(heap, v) && atual->peso < chave[v]) {
                chave[v] = atual->peso;
                pai[v] = u;
                diminuiChave(heap, v, chave[v]);
                contadorDiminuiChave++;  // Contabiliza diminuiChave
                
            }
            atual = atual->prox;
        }
        free(min);
    }

    // Imprime a árvore geradora mínima
    int soma = 0;
    for (int i = 1; i < g->numVertices; i++) {
        if (pai[i] != -1) {
            soma += chave[i];
        }
    }
    printf("Peso total da AGM: %d\n", soma);

    // Estimativa de uso de memória
    long long int memoria = 0;
    memoria += g->numVertices * sizeof(Adj*); 
    for (int i = 0; i < g->numVertices; i++) {
        Adj* atual = g->inicio[i];
        while (atual) {
            memoria += sizeof(Adj);
            atual = atual->prox;
        }
    }
    memoria += g->numVertices * sizeof(int);      
    memoria += g->numVertices * sizeof(int);
    printf("Uso de memoria: %lld bytes\n", memoria);

    // Liberação de memória
    liberaMinHeap(heap, g->numVertices);
    free(pai);
    free(chave);
}

int main(int argc, char *argv[]) {
    clock_t inicio, fim;
    double tempoGasto;
    int V, A;

    if (argc != 2) {
        printf("Uso: %s <caminho_para_grafo_real.txt>\n", argv[0]);
        return 1;
    }

    FILE* arquivo = fopen(argv[1], "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    fscanf(arquivo, "%d", &V);
    fscanf(arquivo, "%d", &A);

    Grafo g;
    inicializaGrafo(&g, V);

    printf("Lendo arestas do arquivo...\n");
    for (int i = 0; i < A; i++) {
        int u, v, peso;
        fscanf(arquivo, "%d %d %d", &u, &v, &peso);
        adicionaAresta(&g, u, v, peso);
    }
    fclose(arquivo);

    inicio = clock();
    prim(&g);
    fim = clock();

    printf("Tempo gasto: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Operacoes extraiMin: %d\n", contadorExtraiMin);
    printf("Operacoes diminuiChave: %d\n", contadorDiminuiChave);

    liberaGrafo(&g);
    return 0;
}