# Guía de uso y ejemplos

Compilación y trazas de ejecución reales del binario construido con `g++ -std=c++11 -o ponts src/ponts.cpp`.

## Compilación

```bash
g++ -std=c++11 -o ponts src/ponts.cpp
./ponts
```

También puedes abrir `Ponts.zpr` con el IDE eduativo **ZinJai** y ejecutar directamente.

## Formato de entrada (por stdin)

```
1. Número de orillas (nodos): entero entre 1 y 20
2. Número de puentes (arcos): entero ≥ 0
3. Para cada puente: dos enteros "n1 n2" con 0 ≤ n1, n2 < número de orillas
```

Los puentes repetidos entre las mismas dos orillas son válidos y esperados (es un multigrafo).

---

## Ejemplo 1 — El mapa histórico de Königsberg (imposible)

Las 4 orillas conectadas con 7 puentes: 2 puentes entre `0-1`, 2 entre `0-2`, 1 entre `0-3`, 1 entre `1-3` y 1 entre `2-3`.

```
Grados resultantes: 5, 3, 3, 3  →  4 vértices impares
```

**Entrada:**

```text
4
7
0 1
0 1
0 2
0 2
0 3
1 3
2 3
```

**Salida real:**

```text
El graf no té camí ni circuít eulèri.
```

Código de salida: `1`. Es exactamente la conclusión de Euler de 1736: como los 4 vértices tienen grado impar, no hay forma de cruzar cada puente una sola vez.

## Ejemplo 2 — Multigrafo con puente repetido (camino abierto)

Dos orillas unidas por **3 puentes**: grados `3` y `3` (exactamente 2 impares), así que sí hay camino — debe empezar en una orilla y acabar en la otra.

**Entrada:**

```text
2
3
0 1
0 1
0 1
```

**Salida real:**

```text
Node d'inici: 1

Solució al graf.:
1 0 1 0
```

Cruza los 3 puentes una única vez: `1 → 0 → 1 → 0`.

## Ejemplo 3 — Circuito euleriano con 7 aristas (ciclo cerrado)

Grafo con grados `4, 4, 3, 3` (2 impares => camino abierto, no circuito):

- `0-1` (x2), `0-2`, `0-3`, `1-2`, `1-3`, `2-3`

**Entrada:**

```text
4
7
0 1
0 1
0 2
0 3
1 2
1 3
2 3
```

**Salida real:**

```text
Node d'inici: 3

Solució al graf.:
3 0 1 0 2 1 3 2
```

Recorre las 7 aristas sin repetir ninguna y termina en una orilla distinta de la inicial (camino euleriano abierto).

---

## Qué cambia el resultado

| Grados impares | Resultado |
|---|---|
| 0 | Circuito euleriano: empiezas y acabas en la misma orilla |
| 2 | Camino euleriano abierto: empiezas y acabas en orillas distintas |
| >2 | "El graf no té camí ni circuít eulèri." |

Para ver el mensaje cambiar, modifica el número de puentes entre dos orillas: cada arista añadida/retirada altera los grados de sus dos extremos.

## Errores de validación

| Entrada | Comportamiento |
|---|---|
| `Nodes <= 0` o `Nodes > 20` | "Nombre de nodes no vàlid." — exit 1 |
| `Arcs < 0` | "Nombre d'arcs no vàlid." — exit 1 |
| Coordenada fuera de `[0, Nodes)` | "Node fora de rang (0..Nodes-1)." — exit 1 |
| Grafo no conexo o >2 impares | "El graf no té camí ni circuít eulèri." — exit 1 |
