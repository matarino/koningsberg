import std.stdio;
import std.array;
import std.algorithm;

class Graph {
    int V;
    int[][] adj;

    this(int v) {
        V = v;
        adj = new int[][V];
    }

    void addEdge(int u, int v) {
        adj[u] ~= v;
        adj[v] ~= u;
    }

    int[] getEulerianCircuit() {
        // 1. Validar que todos los vértices tengan grado par (condición necesaria y suficiente)
        foreach (i; 0 .. V) {
            if (adj[i].length % 2 != 0) {
                writeln("Error: El grafo no tiene un circuito euleriano (hay vértices con grado impar).");
                return [];
            }
        }

        // Duplicamos la estructura del grafo para poder modificarla (consumir aristas)
        int[][] graph = new int[][V];
        foreach (i; 0 .. V) {
            graph[i] = adj[i].dup;
        }

        int[] circuit;
        int[] stack;

        // Encontrar un vértice inicial que tenga aristas
        int curr = 0;
        foreach (i; 0 .. V) {
            if (graph[i].length > 0) {
                curr = i;
                break;
            }
        }

        stack ~= curr;

        // 2. Ejecutar el algoritmo de Hierholzer
        while (stack.length > 0) {
            if (graph[curr].length > 0) {
                // Guardamos el vértice actual en la pila y tomamos un vecino
                stack ~= curr;
                int next = graph[curr].back;
                graph[curr].popBack();

                // Como es un grafo no dirigido, debemos eliminar la arista simétrica (next -> curr)
                auto idx = countUntil(graph[next], curr);
                if (idx != -1) {
                    graph[next] = remove(graph[next], idx);
                }

                curr = next;
            } else {
                // Si ya no hay salidas, agregamos al circuito y retrocedemos en la pila
                circuit ~= curr;
                curr = stack.back;
                stack.popBack();
            }
        }

        // El resultado se obtiene en orden inverso, lo invertimos para el orden correcto
        reverse(circuit);
        return circuit;
    }
}

void main() {
    // Ejemplo de grafo con circuito euleriano (todos los grados son pares)
    // Triángulo (0-1-2) conectado con otro triángulo (2-3-4) a través del vértice 2
    auto g = new Graph(9);
    g.addEdge(0, 4);
    g.addEdge(4, 3);
    g.addEdge(0, 3);
    g.addEdge(1, 3);
    g.addEdge(1, 2);
    g.addEdge(3, 2);
    g.addEdge(3, 6);
    g.addEdge(3, 5);
    g.addEdge(5, 6);

    writeln("Buscando circuito euleriano...");
    auto circuit = g.getEulerianCircuit();

    if (circuit.length > 0) {
        writeln("¡Circuito euleriano encontrado!");
        writeln(circuit);
    }
}