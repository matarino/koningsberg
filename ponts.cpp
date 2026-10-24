#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#define MAX 20

class Puente
{
	int Arcs, Nodes;
	int m[MAX][MAX];
	std::vector<int> path;

public:
	Puente(int,int);
	void InsertaArc(int,int);
	int Grado(int) const;
	bool Conexo() const;
	bool Euleriano(int&) const;
	void Hierholzer(int);
	void Print() const;
};

Puente::Puente(int nodos,int narcs) : Arcs(narcs), Nodes(nodos)
{
	int i,j;
	for ( i=0; i < MAX; i++)
		for ( j=0; j < MAX; j++) { m[i][j] = 0; }
};

void Puente::InsertaArc(int n1,int n2)
{
	if (n1 < 0 || n1 >= Nodes || n2 < 0 || n2 >= Nodes) return;
	m[n1][n2] += 1;
	m[n2][n1] += 1;
};

int Puente::Grado(int n) const
{
	int g = 0;
	for (int c = 0; c < Nodes; c++) g += m[n][c];
	return g;
}

bool Puente::Conexo() const
{
	int start = -1;
	for (int i = 0; i < Nodes; i++) if (Grado(i) > 0) { start = i; break; }
	if (start == -1) return true;

	bool vis[MAX] = {false};
	std::stack<int> st;
	st.push(start);
	vis[start] = true;

	while (!st.empty())
	{
		int u = st.top(); st.pop();
		for (int v = 0; v < Nodes; v++)
		{
			if (m[u][v] > 0 && !vis[v])
			{
				vis[v] = true;
				st.push(v);
			}
		}
	}

	for (int i = 0; i < Nodes; i++)
		if (Grado(i) > 0 && !vis[i]) return false;
	return true;
}

bool Puente::Euleriano(int& start) const
{
	int impares = 0;
	int nodoImpar = -1;
	int nodoConAristas = -1;

	for (int i = 0; i < Nodes; i++)
	{
		int g = Grado(i);
		if (g > 0) nodoConAristas = i;
		if (g % 2 != 0)
		{
			impares++;
			nodoImpar = i;
		}
	}

	if (impares != 0 && impares != 2) return false;
	if (!Conexo()) return false;

	if (impares == 2) start = nodoImpar;
	else start = nodoConAristas;

	return true;
}

void Puente::Hierholzer(int start)
{
	int mm[MAX][MAX];
	int i,j;
	for ( i=0; i < MAX; i++)
		for ( j=0; j < MAX; j++) mm[i][j] = m[i][j];

	std::stack<int> st;
	st.push(start);
	int curr = start;

	while (!st.empty())
	{
		bool hay = false;
		for (int v = 0; v < Nodes; v++)
		{
			if (mm[curr][v] > 0)
			{
				mm[curr][v]--;
				mm[v][curr]--;
				st.push(curr);
				curr = v;
				hay = true;
				break;
			}
		}
		if (!hay)
		{
			path.push_back(curr);
			curr = st.top();
			st.pop();
		}
	}

	std::reverse(path.begin(), path.end());
}

void Puente::Print() const
{
	std::cout << std::endl << "Solució al graf.:" << std::endl;
	for (size_t c = 0; c < path.size(); c++) std::cout << path[c] << " ";
	std::cout << std::endl;
}

int main(void)
{
	int Arcs, Nodes;

	std::cout << "Quants de Nodes té el teu graf (MAX=" << MAX << ")..: ";
	std::cin >> Nodes;
	if (Nodes <= 0 || Nodes > MAX) {
		std::cout << "Nombre de nodes no vàlid." << std::endl;
		return 1;
	}
	std::cout << "Nombre total d'arcs interconectats.......: ";
	std::cin >> Arcs;
	if (Arcs < 0) {
		std::cout << "Nombre d'arcs no vàlid." << std::endl;
		return 1;
	}

	Puente Pont(Nodes, Arcs);

	for (int c = 0; c < Arcs; ++c)
	{
		int n1, n2;
		std::cout << "Coordenada de l'arc nº " << c + 1 << " : ";
		std::cin >> n1 >> n2;
		if (n1 < 0 || n1 >= Nodes || n2 < 0 || n2 >= Nodes) {
			std::cout << "Node fora de rang (0.." << (Nodes-1) << ")." << std::endl;
			return 1;
		}
		Pont.InsertaArc(n1, n2);
	}

	int start;
	if (!Pont.Euleriano(start)) {
		std::cout << std::endl << "El graf no té camí ni circuít eulèri." << std::endl;
		return 1;
	}

	std::cout << "Node d'inici: " << start << std::endl;
	Pont.Hierholzer(start);
	Pont.Print();
	return 0;
}
