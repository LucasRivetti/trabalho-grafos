#!/bin/bash

KRUSKAL_EXEC="./kruskal"
PRIM_EXEC="./prim"
OUTPUT_FILE="resultados_completos.txt"
GRAFOS_DIR="../Dados"
> "$OUTPUT_FILE"

echo "Iniciando a execução de todos os testes..."
echo "Resultados serão salvos em: $OUTPUT_FILE"
echo "----------------------------------------------------"
for tipo in denso esparso real
do
    for i in {1..10}
    do
        INPUT_FILE="${GRAFOS_DIR}/grafo_${tipo}_${i}.txt"

        if [ -f "$INPUT_FILE" ]; then
            echo "--- Executando Kruskal para $INPUT_FILE ---" >> "$OUTPUT_FILE"
            "$KRUSKAL_EXEC" "$INPUT_FILE" >> "$OUTPUT_FILE"
            echo "" >> "$OUTPUT_FILE"

            echo "--- Executando Prim para $INPUT_FILE ---" >> "$OUTPUT_FILE"
            "$PRIM_EXEC" "$INPUT_FILE" >> "$OUTPUT_FILE"
            echo "" >> "$OUTPUT_FILE"
            
        fi
    done
done


GRADE_FILE="${GRAFOS_DIR}/grafo_grade.txt"

if [ -f "$GRADE_FILE" ]; then
    "$KRUSKAL_EXEC" "$GRADE_FILE" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"

    "$PRIM_EXEC" "$GRADE_FILE" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE"
else
fi
