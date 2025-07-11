import random

random.seed(42)

V = 50
A = 75

with open("grafo_real.txt", "w") as f:
    f.write(f"{V}\n{A}\n")
    arestas = set()
    
    # Garante conexão (árvore inicial)
    for i in range(1, V):
        u = i - 1
        v = i
        peso = random.randint(1, 20)
        f.write(f"{u} {v} {peso}\n")
        arestas.add((u, v))
    
    # Adiciona arestas extras
    while len(arestas) < A:
        u = random.randint(0, V-1)
        v = random.randint(0, V-1)
        if u != v and (u, v) not in arestas and (v, u) not in arestas:
            peso = random.randint(1, 20)
            f.write(f"{u} {v} {peso}\n")
            arestas.add((u, v))