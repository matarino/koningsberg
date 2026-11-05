# Referencia de la API — clase `Puente`

Fuente única de verdad: [`src/ponts.cpp`](../src/ponts.cpp). C++11, sin dependencias externas, máximo 20 nodos (`#define MAX 20`).

## Modelo

La clase modela un **multigrafo no dirigido**: las orillas de la ciudad son vértices (`0 .. Nodes-1`) y los puentes son aristas. Varios puentes pueden unir las mismas dos orillas — la matriz de adyacencia guarda el **número de puentes** entre cada par de orillas (`m[i][j] += 1`, no `m[i][j] = 1`).

Estado interno:

| Miembro | Tipo | Descripción |
|---|---|---|
| `Nodes` | `int` | Número de orillas/vértices del grafo (1..20) |
| `Arcs` | `int` | Número total de puentes declarados |
| `m[MAX][MAX]` | `int` | Matriz de adyacencia multigrafo: `m[i][j]` = puentes entre `i` y `j` |
| `path` | `std::vector<int>` | Camino euleriano resultante tras llamar a `Hierholzer()` |

## Constructor

```cpp
Puente(int nodos, int narcs)
```

Inicializa a cero toda la matriz `m`. No valida rangos: la validación se hace en `main()` y dentro de `InsertaArc`.

## Métodos

### `void InsertaArc(int n1, int n2)`

Añade un puente entre las orillas `n1` y `n2`. Es simétrico: incrementa `m[n1][n2]` y `m[n2][n1]`, y admite puentes repetidos. **Silencia las aristas fuera de rango** (`n1 < 0 || n1 >= Nodes || n2 < 0 || n2 >= Nodes` → no-op, sin excepciones).

### `int Grado(int n) const`

Grado del vértice `n`: suma de la fila `n` de la matriz. En un multigrafo, cada puente repetido cuenta individualmente (la orilla del mapa de Königsberg con 5 puentes devuelve 5).

### `bool Conexo() const`

DFS iterativa con `std::stack` desde el primer vértice con grado > 0. Devuelve `true` si todo vértice con grado > 0 es alcanzable; los vértices aislados (grado 0) no rompen la conectividad. Un grafo vacío se considera conexo.

### `bool Euleriano(int& start) const`

Implementa el teorema de Euler. Devuelve `true` si existe camino/circuito euleriano, y calcando en `start` el nodo óptimo de salida:

- Cuenta los vértices de grado impar. Si no son exactamente **0 o 2** → `false` (caso de Königsberg histórico: 4 impares).
- Exige `Conexo()`: si el grafo está fragmentado → `false`.
- Si hay 2 impares: `start` = uno de los vértices impares (camino abierto, empieza y acaba en orillas distintas).
- Si hay 0 impares: `start` = el último vértice con aristas (circuito cerrado).

### `void Hierholzer(int start)`

Construye la ruta en `path` en **O(Aristas)**. Algoritmo:

1. Copia la matriz en una matriz de trabajo `mm` (las aristas se van *consumiendo*: `mm[curr][v]--; mm[v][curr]--;`).
2. Pila con `start`; mientras el vértice actual tenga aristas disponibles, avanza a un vecino empujando el nodo anterior a la pila.
3. Cuando el vértice actual se queda sin aristas, lo añade a `path` y retrocede en la pila → aquí se van ensamblando los subciclos de Hierholzer.
4. `std::reverse(path)` final: el resultado sale en orden correcto.

Precondición: se debe haber comprobado `Euleriano(start)` antes de llamarlo; con un grafo no euleriano el resultado es indefinido.

### `void Print() const`

Imprime `path` como secuencia de índices de orillas separados por espacios, bajo el rótulo `Solució al graf.:`.

## Flujo de `main()`

```
stdin: Nodes → Arcs → Arcs pares "n1 n2"
validación: 1 ≤ Nodes ≤ MAX, Arcs ≥ 0, coordenadas dentro de [0, Nodes)
si Euleriano falla → "El graf no té camí ni circuít eulèri." (exit 1)
si pasa     → hierholzer(start) + Print() (exit 0)
```

## Limitaciones conocidas

- Máximo **20 nodos** (`MAX 20`, matriz estática).
- No es Thread-safe ni reutilizable tras una ejecución de `Hierholzer` (el `path` se acumula; no se borra entre llamadas).
- `Grado()` sobre un nodo con `n >= Nodes` lee memoria sin inicializar: los índices ambientales deben validarse antes.
