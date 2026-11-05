# 🌉 Ponts de Königsberg — El camí únic

Juego/calculadora educativa en C++ inspirada en el **clásico problema de los siete puentes de Königsberg** (1736), el reto que dio origen a la **teoría de grafos** gracias a Leonhard Euler.

> ¿Se puede recorrer la ciudad cruzando **cada puente exactamente una vez**? Euler demostró que no… y este programa lo comprueba con tus propios grafos. 😎

## 📖 Contexto histórico

En la ciudad prusiana de **Königsberg** (hoy Kaliningrado) el río Pregolya rodeaba la isla de Kneiphof, uniendo cuatro zonas por siete puentes:

```text
         (3)
   A ──────── B        A, D = orillas norte/sur
  /|        /|         B, C = orillas este/oeste
 (1) (4)  (5) (6)      (n)  = puentes
  / |      |  \
 C ───(2)──┼── D
    \      (7)
     \_____|/
```

Euler lo razonó sustituyendo orillas por **vértices** y puentes por **aristas**. Su conclusión:

| Grados (impares) | ¿Camino euleriano? |
|---|---|
| 0 | Sí: ciclo euleriano (empiezas y acabas en el mismo sitio) |
| 2 | Sí: camino abierto (uno de los dos vértices impares es inicio y el otro es fin) |
| >2 (el caso de Königsberg: grados 3, 3, 5 y 3) | ❌ Imposible |

Königsberg tenía **4 orillas conectadas por 7 puentes y todos los grados son impares** → no tiene solución. Este programa implementa exactamente esa demostración en código.

## 🧩 Cómo funciona el proyecto

El proyecto modela un **multigrafo** formado por orillas (vértices) y puentes (aristas), y calcula el **camino euleriano** (el "únic camí"):

1. Crea el grafo indicando número de nodos y arcos → `Puente(nodos, aristas)`
2. Añade cada puente con `InsertaArc(n1, n2)` (multigrafo: admite varios puentes entre las mismas dos orillas)
3. Comprueba la **conectividad** con una DFS sobre los vértices con grado > 0 (`Conexo()`)
4. Comprueba la **condición de Euler** contando grados (`Grado(n)`, `Euleriano(puntoDePartida)`)
5. Si es viable, construye el recorrido con el **algoritmo de Hierholzer** (`Hierholzer()`) y lo imprime
6. Si hay más de 2 vértices de grado impar → `No existe solución` (como en el Königsberg original)

## 🔧 Compilación (ZinJai / compilador)

- El proyecto está hecho con **ZinJai** (IDE educativo, proyecto `Ponts.zpr`):
  abre `Ponts.zpr` con ZinJai y pulsa ▶ Ejecutar.
- Con el compilador estándar:

```bash
g++ -std=c++11 -o ponts src/ponts.cpp
./ponts
```

## ⌨️ Ejemplo de uso

```text
Nodos: 4   Arcos: 7        // el mapa de Königsberg
Arc(0,1) … etc.
Resultado: No es posible recorrer todos los puentes una sola vez
```

Cambia los grados de los nodos y verás cómo el mensaje cambia a
`Camino euleriano: 3 1 0 2 1 3 …` cuando el grafo cumple la condición de Euler.

## 📁 Estructura del proyecto

```text
koningsberg/
├── Ponts.zpr        # proyecto de ZinJai
├── README.md
├── doc/             # referencia del algoritmo de Hierholzer (implementación de estudio)
└── src/
    └── ponts.cpp    # clase `Puente`: matriz de adyacencia, Euler y Hierholzer
```

## 🛠️ Detalles de implementación

- `Puente::m[MAX][MAX]`: matriz de adyacencia **multigrafo** — los puentes repetidos se acumulan (`m[i][j] += 1`)
- Condición de Euler: grafo conexo y **0 o 2 vértices de grado impar**
- Hierholzer: recorre aristas sin repetir con una pila auxiliar y va descartando subciclos hasta tener el camino completo en `path`

## 🤖 Para IAs / herramientas agénticas

Este repo expone su documentación vía [GitMCP](https://gitmcp.io/matarino/koningsberg):

[![GitMCP](https://img.shields.io/endpoint?url=https://gitmcp.io/badge/matarino/koningsberg)](https://gitmcp.io/matarino/koningsberg)

## 🤝 Contribuciones

Ideas bien recibidas: interfaz de entrada del grafo por consola, dibujar el grafo, cargas de mapas de puentes reales, etc.

## 📜 Licencia

Ver [LICENSE](LICENSE).

## Referencias

- Euler, L. — *Solutio problematis ad geometriam situs pertinentis* (1736)
- Algoritmo de **Hierholzer** (1873): construcción lineal del camino euleriano
- [Seven Bridges of Königsberg](https://en.wikipedia.org/wiki/Seven_Bridges_of_Königsberg)
