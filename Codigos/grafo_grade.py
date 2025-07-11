N = 30  # 30x30 grid
V = N * N
A = 2 * N * (N - 1)  # Cálculo exato para grade

with open("grafo_grade.txt", "w") as f:
    f.write(f"{V}\n{A}\n")
    
    # Conexões horizontais
    for i in range(N):
        for j in range(N - 1):
            u = i * N + j
            v = u + 1
            f.write(f"{u} {v} 1\n")
    
    # Conexões verticais
    for i in range(N - 1):
        for j in range(N):
            u = i * N + j
            v = u + N
            f.write(f"{u} {v} 1\n")