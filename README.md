<<<<<<< HEAD
# Trabalho Final – Grafos: Análise Comparativa de Kruskal vs Prim

Repositório do trabalho final da disciplina de Grafos (UFSJ – 1/2025)  
Profª Jesuliana N. Ulysses

---

## Estrutura do Repositório

```
├── Trabalho Grafos.pdf                 # Relatório final em formato PDF
├── README.md                     
├── codigos/                      # Implementações em C
│   ├── kruskal.c
│   └── prim.c
├── analises/                     # Planilha de análise comparativa
│   └── .....
└── dados/                        # Grafos de entrada para os testes
    ├── grafo_esparso.txt
    ├── grafo_denso.txt
    └── ... 
```

---

## Objetivo do Projeto

Comparar, em teoria e prática, os algoritmos de **Árvore Geradora Mínima** (AGM) de **Kruskal** e **Prim** em grafos:
- **Esparsos** (poucas arestas)
- **Densos** (muitas arestas)

O estudo inclui:
1. Revisão teórica de AGM e propriedades (corte & ciclo)  
2. Diferenças conceituais e operacionais entre Kruskal e Prim  
3. Estruturas de dados usadas (Union-Find, min-heap, representações de grafo)  
4. Implementação em C e testes práticos  
5. Medição de desempenho (tempo, operações, uso de memória)  
6. Análise comparativa via planilha e gráficos  
7. Discussão de aplicações reais (redes de computadores, energia, água, transporte)

---

## Como Usar

1. **Relatório**  
   Abra e leia `Trabalho Grafos.pdf` para a fundamentação teórica, metodologia, resultados e conclusão.

2. **Compilar e Executar os Códigos**  
   ```sh
   cd codigos
   gcc kruskal.c -o kruskal
   gcc prim.c    -o prim
   ./kruskal ../dados/grafo_esparso.txt
   ./prim    ../dados/grafo_esparso.txt
   ```
   Substitua `grafo_esparso.txt` por qualquer arquivo em `dados/`.

3. **Análise no Excel**  
   - Abra `analises/Teste.xlsx`  
   - Preencha resultados (peso, tempo, etc.) nas abas **Dados dos Grafos** e **Resultados dos Algoritmos**  
   - Navegue até **Gráficos Comparativos** e insira gráficos automáticos

4. **Adicionar Novos Testes**  
   - Coloque arquivos de grafo em `dados/`  
   - Atualize os caminhos no código C ou na planilha  
   - Repita testes e regenere gráficos

---

## Estrutura de Análise

- **Dados dos Grafos**  
  | Identificação | # Vértices | # Arestas | Tipo        | Observações |
  | ------------- | ---------- | --------- | ----------- | ----------- |
  | Grafo 1       |            |           | Esparso/Denso |           |
  | Grafo 2       |            |           | Esparso/Denso |           |

- **Resultados dos Algoritmos**  
  | Grafo   | Algoritmo | Peso AGM | Tempo (ms) | Estrutura      | Complexidade | Observações |
  | ------- | --------- | -------- | ---------- | -------------- | ------------ | ----------- |
  | Grafo 1 | Kruskal   |          |            | Union-Find     |              |             |
  | Grafo 1 | Prim      |          |            | Min-Heap       |              |             |
  | Grafo 2 | Kruskal   |          |            | Union-Find     |              |             |
  | Grafo 2 | Prim      |          |            | Min-Heap       |              |             |

- **Gráficos Comparativos**  
  - **Peso AGM** por algoritmo e grafo (colunas agrupadas)  
  - **Tempo de Execução** por algoritmo e grafo (barras agrupadas)

---

## Autores

- Lucas Rivetti  
- Lucas Campelo  
- Augusto Cezar  
- José Lopes  
- Bruno Henrique  

🗓️ Entrega: 17/07/2025

---
  
=======
# trabalho-grafos
>>>>>>> 6276561953e9612d61009c399498337b62bb9a37
