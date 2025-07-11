import random

random.seed(42)

V = 500
A = 100000

with open("grafo_denso.txt", "w") as f:
    f.write(f"{V}\n{A}\n")
    arestas = set()
    
    # Garante que o grafo é conexo (árvore inicial)
    for i in range(1, V):
        u = i - 1
        v = i
        peso = random.randint(1, 50)
        f.write(f"{u} {v} {peso}\n")
        arestas.add((u, v))
    
    # Adiciona arestas aleatórias até atingir 100K
    while len(arestas) < A:
        u = random.randint(0, V-1)
        v = random.randint(0, V-1)
        if u != v and (u, v) not in arestas and (v, u) not in arestas:
            peso = random.randint(1, 50)
            f.write(f"{u} {v} {peso}\n")
            arestas.add((u, v))