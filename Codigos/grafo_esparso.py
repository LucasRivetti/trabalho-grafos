import random

random.seed(42)  # Para resultados reproduzíveis

V = 1000
A = 1500

with open("grafo_esparso.txt", "w") as f:
    f.write(f"{V}\n{A}\n")
    arestas = set()
    
    # Garante que o grafo é conexo (árvore inicial)
    for i in range(1, V):
        u = i - 1
        v = i
        peso = random.randint(1, 100)
        f.write(f"{u} {v} {peso}\n")
        arestas.add((u, v))
    
    # Adiciona arestas aleatórias restantes
    while len(arestas) < A:
        u = random.randint(0, V-1)
        v = random.randint(0, V-1)
        if u != v and (u, v) not in arestas and (v, u) not in arestas:
            peso = random.randint(1, 100)
            f.write(f"{u} {v} {peso}\n")
            arestas.add((u, v))