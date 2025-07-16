
# Trabalho Final – Grafos: Análise Comparativa de Kruskal vs Prim

Repositório do trabalho final da disciplina de Grafos (UFSJ – 1/2025)  
Profª Jesuliana N. Ulysses

---

## Estrutura do Repositório

```
├── Trabalho Grafos.pdf              # Relatório final em formato PDF
├── README.md
├── Teoria_Grafos.pdf                # Teoria para a compreensão do trabalho     
├── codigos/                         # Implementações em C
│   ├── kruskal.c
│   ├── prim.c
│   ├── $executar_testes.sh
│   ├── grafo_denso.py               # Criação de grafos com algoritimos em python
│   ├── grafo_esparso.py
│   ├── grafo_grade.py
|   └── grafo_real.py
├── analises/                       # Resultados de análise comparativa
│   ├── Comparativo Custo MST.pdf
|   ├── Operações Find.pdf
|   ├── Operações Union.pdf
|   └── ...
└── dados/                          # Grafos de entrada para os testes
    ├── grafo_esparso_1.txt
    ├── grafo_denso_1.txt
    ├── grafo_grade.txt
    ├── grafo_real_1.txt
    └── ...
```

---

## Objetivo do Projeto

Comparar, em teoria e prática, os algoritmos de **Árvore Geradora Mínima** (AGM) de **Kruskal** e **Prim** em grafos:
- **Esparsos** (poucas arestas)
- **Densos** (muitas arestas)
- **Grade** (matriz)
- **Real** (estruturas do dia a dia)

O estudo inclui:
1. Revisão teórica de AGM e propriedades (corte & ciclo)  
2. Diferenças conceituais e operacionais entre Kruskal e Prim  
3. Estruturas de dados usadas (Union-Find, min-heap, representações de grafo)  
4. Implementação em C e testes práticos  
5. Medição de desempenho (tempo, operações, uso de memória)  
6. Análise comparativa via texto e gráficos  
7. Discussão de aplicações reais (redes de computadores, energia, água, transporte)

--

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

3. **Análise em massa**  
   - Abra `analises\`  
   - Analise resultados (peso, tempo, etc.) 

4. **Adicionar Novos Testes**  
   - Coloque arquivos de grafo em `dados/`  
   - Atualize os caminhos no código C ou na planilha  
   - Repita testes e regenere gráficos

---

## Estrutura de Análise

- **Dados dos Grafos**  
  | Identificação      | # Vértices | # Arestas | Tipo        |        Observações           |
  | ------------------ | ---------- | --------- | ----------- | ---------------------------- |
  | Grafo_denso_1.txt  |    500     |  100000   |    Denso    |    grafo extremamente denso  |
  | Grafo_esparso_1.txt|    1000    |   1500    |   Esparso   |           -------            |
  | Grafo_grade.txt    |    900     |   1740    |    Grade    |           -------            |
  | Grafo_real_1.txt   |    50      |    75     |    Real     |    simula um fluxo de água   |

- **Resultados dos Algoritmos**  
  | Grafo               | Algoritmo | Peso AGM | Tempo (s)  | Estrutura      | Uso de memória (em bytes) |
  | ------------------- | --------- | -------- | ---------- | -------------- | ------------------------- |
  | Grafo_denso_1.txt   | Kruskal   |   499    |  0.033593  | Union-Find     |          1204000          |             
  | Grafo_denso_1.txt   | Prim      |   499    |  0.047412  | Min-Heap       |          3208000          |             
  | Grafo_esparso_1.txt | Kruskal   |  35062   |  0.000494  | Union-Find     |           26000           |             
  | Grafo_esparso_1.txt | Prim      |  35062   |  0.001121  | Min-Heap       |           64000           |             
  | Grafo_grade.txt     | Kruskal   |   899    |  0.000416  | Min-Heap       |           28080           |             
  | Grafo_grade.txt     | Prim      |   899    |  0.000588  | Min-Heap       |           70080           |             
  | Grafo_real_1.txt    | Kruskal   |   341    |  0.000040  | Min-Heap       |           1300            |             
  | Grafo_real_1.txt    | Prim      |   341    |  0.000035  | Min-Heap       |           3200            |             

- **Gráficos Comparativos**  
  - **Peso AGM** por algoritmo e grafo (colunas agrupadas)  
  - **Tempo de Execução** por algoritmo e grafo (barras agrupadas)
  - **Uso de Memoria** por algoritmo (barras agrupadas)
  - **Operações Find** por algoritmo (barras agrupadas)
  - **Operações Union** por algoritmo (barras agrupadas)  
---

## Autores

- Lucas Rivetti  
- Lucas Campelo  
- Augusto Cezar  
- José Lopes  
- Bruno Henrique  

🗓️ Entrega: 17/07/2025

---
