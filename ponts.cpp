#include <iostream>
#include <stdlib.h>

#define MAX 20

class Puente
{
	int *v;
    int Arcs, Nodes, Vindex;
	int m[MAX][MAX];

public:
	Puente (int,int);
	~Puente() { delete[] v; }

	bool ParseGraf(int,int);
	int GetIndex() { return Vindex; }
	int CercaArc(int,int);
	void InsertaArc(int,int);
	void LlevaArc(int,int);
	void PutNode(int node) { v[Vindex] = node; }
	void IncIndex() { Vindex++; }
	int  GetNode() { return v[Vindex]; }
	void DecIndex() { Vindex--; }
	void MatriuACeros(void);
	void Print();
};

unsigned long Fact(int n)
{
	unsigned long s = 1;
	if (n == 0) return 1;
	if (n >= 3) for (int c=2; c <= n; c++)  s = s * c;
	   else return n;
	return s;
};

Puente::Puente(int nodos,int narcs)
{
	long var=0;
	Vindex = 0;
	Arcs = narcs;
	Nodes = nodos;
	var = Fact(Nodes)/(2 * Fact(Nodes-2)) + 1;
	v = new int[var];
	MatriuACeros();
};

void Puente::Print()
{
  std::cout << std::endl << "Solució al graf.:" << std::endl;
  for (int c=0; c < Arcs+1; c++) std::cout << v[c] << " ";
  std::cout << std::endl;
};

int Puente::CercaArc(int n2, int n1)
{
  int c;
  if (n2 >= Nodes)
	return n2;
  for ( c = n2; c < Nodes; c++) {
	if (m[n1][c])
		return c;
  }
  return c;
}

void Puente::InsertaArc(int n1,int n2)
{
	m[n1][n2] += 1;
	m[n2][n1] += 1;
};

void Puente::LlevaArc(int n1,int n2)
{
	m[n1][n2] -= 1;
	m[n2][n1] -= 1;
};

void Puente::MatriuACeros(void)
{
  int i,j;
  for ( i=0; i < MAX; i++)
	for ( j=0; j < MAX; j++) { m[i][j] = 0; }
};

bool Puente::ParseGraf(int num1,int num2) {

	int n1 = num1;
	int n2 = num2;

	while ( GetIndex() < Arcs) {
		if( (n2 = CercaArc(n2,n1)) >= Nodes)
		{
			if ( GetIndex() >= 1)
			{
				n2 = GetNode();
				DecIndex();
				n1 = GetNode();
				InsertaArc(n1,n2);
				n2++;
				continue;
			}

			n1++;

			if ( n1 >= Nodes)
				return false;

			PutNode(n1);
			n2 = 0;
			continue;
		}
		LlevaArc(n1,n2);
		IncIndex();
		PutNode(n2);
		n1 = n2;
		n2 = 0;
	}
	return true;
}

int main(void)
{
	int Arcs,Nodes;

	std::cout << "Quants de Nodes té el teu graf (MAX="<<MAX<<")..: ";
	std::cin >> Nodes;
	std::cout << "Nombre total d'arcs interconectats.......: ";
	std::cin >> Arcs;

	Puente Pont(Nodes,Arcs);

	int n1=0;
    int n2=0;

    for (int c = 0; c < Arcs; ++c) {
	  std::cout << "Coordenada de l'arc nº " << c+1 << " : ";
	  std::cin >> n1 >> n2;
	  Pont.InsertaArc(n1, n2);
	};

	std::cout << "A partir de quin arc cerc la solució...: ";
	std::cin >> n1 >> n2;

	Pont.PutNode(n1);

	if (Pont.ParseGraf(n1,n2)) {
        Pont.Print();
        return 0;
    } else {
		std::cout << std::endl << "Desde l'arc indicat el graf no té solució." << std::endl;
		return 1;
	}
}


