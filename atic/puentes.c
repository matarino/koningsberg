#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>

int m[10][10];
int n,v[45];
int narc,nodos;

int busca_arco(int n2,int n1);

int main(void)
{
  int c,n1,n2;

// clrscr();
  printf("\nDe cuantos NODOS est  compuesto tu grafo (MAX-10)..: ");
  scanf ("%d",&nodos);
  printf("\nCual es el número total de ARCOS interconectados...: ");
  scanf ("%d",&narc);

  c = narc;
  while (c) {
    printf("Coordenadas del arco nº: %d :",(narc-c)+1);
    scanf("%d%d",&n1,&n2);
    m[n1][n2] += 1;
    m[n2][n1] += 1;
    c--;
   };

  printf("\nA partir de que ARCO busco una soluci¢n (X-Y).: ");
  scanf ("%d%d",&n1,&n2);

  n = 0;
  v[n] = n1;

  while (n < narc) {
    if ((n2=busca_arco(n2,n1)) >= nodos) {
       if (n > 1) {
            n2 = v[n];
            n--;
            n1=v[n];
            m[n1] [n2] += 1;
            m[n2] [n1] += 1;
            n2++;
            continue;
        }
        n1++;
        if (n1 > nodos) {
            printf("\nDesde los nodos indicados, el grafo no tiene solución!\n\n");
            exit(1);
        }
        v[n] = n1;
        n2 = 0;
        continue;
    }
    m[n1] [n2] -= 1;
    m[n2] [n1] -= 1;
    n++;
    v[n] = n2;
    n1   = n2;
    n2   = 0;
  }
  printf("\nSolución al grafo:\n\n");
  for (c=0; c < narc+1; c++) printf("%d ",v[c]);
  return 0;
}    /* Fin del programa */

int busca_arco(int n2,int n1)
{
  int c;

  if (n2 >= nodos)
     return n2;
  for (c=n2; c < nodos; c++) {
      if (m[n1][c]) {
         return c;
       }
  }
  return c;
}
