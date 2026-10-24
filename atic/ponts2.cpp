/**
#include <iostream.h>
**/
#include <stdlib.h>
#include <conio.h>

#define MAX 20

class Puente
{
	int *v, Arcs, Nodes, Vindex;
	int *m[MAX];
public:
	Puente (int,int);
	~Puente() { delete v; }

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
	v = new int [var];
	MatriuACeros();
};

void Puente::Print()
{
  cout << endl << "Soluci¢ al graf.:" << endl;
  for (int c=0; c < Arcs+1; c++) cout << v[c] << " ";
  cout << endl;
};

int Puente::CercaArc(int n2, int n1)
{
  if (n2 >= Nodes)	return n2;
  for (int c = n2; c < Nodes; c++) {
	 if (m[n1][c])  return c;
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
  for ( i=0; i<MAX; i++)
	for ( j=0; j<MAX; j++) { m[i][j] = 0; }
};


void main()
{
	int n1,n2,Arcs,Nodes;
	clrscr();
	cout << "Cuants de Nodes t el teu graf (MAX="<<MAX<<")......: ";
	cin >> n1;
	Nodes = n1;
	cout << "Nombre total d'arcs interconectats.......: ";
	cin >> n2;
	Arcs = n2;

	Puente Pont(Nodes,Arcs);

	n1=0; n2=0;
	for (int c = 0; c < Arcs; ++c) {
	  cout << "Coordenada de l'arc n§ " << c+1 << " : ";
	  cin >> n1 >> n2;
	  Pont.InsertaArc(n1, n2);
	};

	cout << "A partir de quin arc cerc la soluci¢ ..: ";
	cin >> n1 >> n2;

	Pont.PutNode(n1);

	while (Pont.GetIndex() < Arcs) {
		if((n2=Pont.CercaArc(n2,n1)) >= Nodes) {
			if (Pont.GetIndex() > 1) {
				n2 = Pont.GetNode();
				Pont.DecIndex();
				n1 = Pont.GetNode();
				Pont.InsertaArc(n1,n2);
				n2++;
				continue;
			}
			n1++;
			if ( n1 >= Nodes) {
				cout << endl << "Desde l'arc indicat el graf no t soluci¢." << endl;
				exit(1);
			}
			Pont.PutNode(n1);
			n2 = 0;
			continue;
		}
		Pont.LlevaArc(n1,n2);
		Pont.IncIndex();
		Pont.PutNode(n2);
		n1 = n2;
		n2 = 0;
	}
	Pont.Print();
}


