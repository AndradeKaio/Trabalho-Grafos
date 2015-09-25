/***********************************************************************
* Pontificia Universidade Catolica de Minas Gerais 
* Ciencia da Computacao 
* Algoritmos em Grafos
* Prof. Max do Val Machado
************************************************************************/


//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>

using namespace std;


//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_VERTICE		 		500
#define MAX_INT         	0x7FFFFFFF
#define NULO						  -1
#define BRANCO						0
#define PRETO						  1
#define INIFITY           0x7FFFFFFF 
//=====================================================================
// DEFINICAO DE TIPOS
//=====================================================================
typedef short boolean;

typedef int Vertice;
typedef int Peso;

struct Aresta{
  Vertice vi, vj;
  Peso peso;
};



//=====================================================================
// CLASSE GRAFO
//=====================================================================
class Grafo
{
   private:


      int numVertice, 
          numAresta, componentes;


      bool visitados[MAX_VERTICE];
      int  fila[MAX_VERTICE];

      Peso matriz[MAX_VERTICE][MAX_VERTICE];
      

          
   public:
      //--------------------------------------------------------------------
      // Construtor
      //--------------------------------------------------------------------
      Grafo()
      {
         numVertice     = 0;
         numAresta      = 0;
         componentes    = 0;
         excluirTodasArestas();
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // Destrutor
      //--------------------------------------------------------------------
      ~Grafo()
      {
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // lerGrafo: Realiza a leitura do grafo no arquivo.
      //--------------------------------------------------------------------
      boolean lerGrafo()
      {
         boolean resp;
         int temp;
         excluirTodasArestas();

         //Ler o numero de vertices
         cin >> temp;
         setNumVertice(temp);

         resp = (numVertice > 0) ? true : false; 

         for(int i = 0; i < numVertice; i++)
         {
            inserirAresta(i, i, NULO);
            for(int j = i+1; j < numVertice; j++)
            {	
               cin >> temp;
               //cout << "Peso inserido " << temp << "\n";
               //cout << "Numero aresta "<< " " << numAresta << "\n";
               inserirAresta(i, j, temp);
               inserirAresta(j, i, temp);
            }
         }
         return resp;
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // imprimir: Imprime o grafo.
      //--------------------------------------------------------------------
      void imprimir()
      {
         int i = 0, j = 0;

         printf("\nN = (%i)\n\t",numVertice);
         for(i = 0; i < numVertice; i++)
         {
            if (i >= 100)
            {
               printf("\t(%i) ",i);
            }
            else if(i >= 10)
            {
               printf("\t(0%i) ",i);
            }
            else
            {
               printf("\t(00%i) ",i);
            }
         }

         for(i = 0; i < numVertice; i++)
         {
            if (i >= 100)
            {
               printf("\n(%i) - ",i);
            }
            else if(i >= 10)
            {
               printf("\n(0%i) - ",i);
            }
            else
            {
               printf("\n(00%i) - ",i);
            }

            for(j = 0; j < numVertice; j++)
            {
               if(matriz[i][j] == NULO)
               {
                  printf("\t. ");
               }
               else
               {
                  printf("\t%i ",matriz[i][j]);
               }
            }
         }

         printf("\n");
      }//-------------------------------------------------------------------

   private:

      //--------------------------------------------------------------------
      // inserirAresta: Insere uma nova aresta.
      //--------------------------------------------------------------------
      void inserirAresta(Vertice v1, Vertice v2, Peso peso)
      {

         if(v1 > MAX_VERTICE)
         {
            printf("ERRO! Vertice %i nao existe no grafico", v1);
            return;
         }

         if(v2 > MAX_VERTICE)
         {
            printf("ERRO! Vertice %i nao existe no grafico", v2);
            return;
         }

         if(matriz[v1][v2] == NULO)
         {
            matriz[v1][v2] = peso;
            if(peso != NULO && isAresta(v2,v1) == false)
               numAresta++;
         }      
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // isAresta: Retorna true se existe a aresta.
      //--------------------------------------------------------------------
      boolean isAresta(Vertice v1, Vertice v2)
      {
         return (matriz[v1][v2] != NULO);
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // getAresta: Retorna o peso da aresta.
      //--------------------------------------------------------------------
      Peso getAresta(Vertice v1, Vertice v2)
      {
         return (matriz[v1][v2]);
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // excluirAresta: Exclui uma aresta.
      //--------------------------------------------------------------------
      void excluirAresta(Vertice v1, Vertice v2)
      {

         if(v1 > numVertice)
         {
            printf("ERRO! Vertice %i nao existe no grafico",v1);
            return;
         }

         if(v2 > numVertice)
         {
            printf("ERRO! Vertice %i nao existe no grafico",v2);
            return;
         }

         if(matriz[v1][v2] != NULO)
         {
            matriz[v1][v2] = NULO;
            numAresta--;
         }      
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // excluirTodasArestas: Exclui todas as arestas.
      //--------------------------------------------------------------------
      void excluirTodasArestas()
      {
         for(int i = 0; i < MAX_VERTICE; i++)
         {
            matriz[i][i] = NULO;
            for(int j = i + 1; j < MAX_VERTICE; j++)
            {
               matriz[i][j] = matriz[j][i] = NULO;
            }
         }
         numAresta = 0;
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // setNumVertice: Altera a variavel numVertice.
      void setNumVertice(int nVertice)
      {

         if(nVertice > MAX_VERTICE)
         {
            printf("ERRO: Numero de vertices\n");
            return;
         }

         numVertice = nVertice;
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // getNumVertice: Retorna a numVertice
      //--------------------------------------------------------------------
      int getNumVertice()
      {
          return numVertice;
      }//--------------------------------------------------------------------



   public:

      void imprimirVerticeAresta()
      {
         cout << numVertice << " " << numAresta << "\n";
      }//--------------------------------------------------------------------


      /**
       * Inicia vetor de visitados como false/naovisitado
       */
      void iniciaVisitados()
      {
         for (int i = 0; i < numVertice; ++i)
         {
            visitados[i] = false;
         }
      }//--------------------------------------------------------------------


      /**
       * pesquisaProfundidade: Algoritmo de caminhamento em Grafo utilizando o metodo
       * de Busca em Profundidade.
       */
      void pesquisaProfundidade()
      {
      		for (int i = 0; i < numVertice; ++i)
            {
               if(visitados[i] == false)
               {
                  componentes++;
                  visite(i);
               }
            }
      }//--------------------------------------------------------------------


      //--------------------------------------------------------------------
      // visite: Visita os vinhos de um vertice nao visitado na matriz
      //--------------------------------------------------------------------
      void visite(Vertice v)
      {
            visitados[v] = true;
            for( int i = 0; i < numVertice; i++)
            {
               if(isAresta(i,v) && visitados[i] == false)
                  visite(i);
            }
      }//--------------------------------------------------------------------


      
      /**
       * pesquisaLargura: Algoritmo de caminhamento em Grafo utilizando o metodo
       * de Busca em Largura.
       */
      void pesquisaLargura()
      {

         int inicioFila = 0;
         int finalFila  = 0;

         iniciaVisitados();
         
         for (int i = 0; i < numVertice; ++i)
         {
            if(visitados[i] == false)
            {
               componentes++;
               pesquisaLargura(i, &inicioFila, &finalFila);
            }
         }

      }

      void pesquisaLargura(Vertice v, int* inicioFila, int* finalFila)
      {
         for (int i = 0; i < numVertice; ++i)
         {
            if(isAresta(v,i) && visitados[v] == false)
            {
               visitados[i] = true;
               fila[*finalFila] = i;
               *finalFila++;
            }
         }

         if( fila[*inicioFila] != NULO && *finalFila != *inicioFila)
         {
            int x = fila[*inicioFila];
            *inicioFila++;
            pesquisaLargura(x, inicioFila, finalFila);
         }
         else
         {
            cout << "ERRO! Fila vazia!";
         }
                  
      }//--------------------------------------------------------------------

      /**
       *
       */

      void isBipartite()
      {
        int inicioFila = 0;
        int finalFila  = 0;
        int * cores = new int[numVertice];
        for (int i = 0; i < numVertice; ++i)
         cores[i] = -1;

        iniciaVisitados();
         
        for (int i = 0; i < numVertice; ++i)
        {
           if(visitados[i] == false)
           {
              componentes++;
              pesquisaLargura(i, &inicioFila, &finalFila);
           }
        }
      }

      /**
       * isConexo: Metodo que retorna verdadeiro se houver ao menos um caminho
       * entre todos os vertices do grafo.
       */
      bool isConexo()
      {
         bool resp = false;
         pesquisaProfundidade();
         if(componentes <= 1)
         {
            resp = true;
         }
         return resp;
      }


      //--------------------------------------------------------------------
      //                            isEuleriano
      //--------------------------------------------------------------------
      /**
       * isEuleriano: Método que verifica se um determinado Grafo é Euleriano
       * @return true caso seja Euleriano 
       * @param Grafo f
       */

      bool isEuleriano()
      {
         bool resp = false;
         if(isConexo())
         {
            resp = true;
            for (int i = 1; i < numVertice; ++i)
            {
               if( grauVertice(i) % 2 != 0)
               {
                  resp = false;
                  i = numVertice;
               }
            }
         }
         return resp;
      }
      //--------------------------------------------------------------------

      /**
       * isUnicursal: Metodo que verifica se existe ao menos 2 vertices com grau
       * impar em um grafo conexo.
       */
      bool isUnicursal()
      {
         bool resp = false;
         int  x = 1;
         if(isConexo())
         {
            for (int i = 1; i < numVertice; ++i)
            {
               if( grauVertice(i) % 2 != 0)
               {
                  x++;
               }
            }
            if( x % 2 == 0)
            {
               resp = true;
            }
         }
         return resp;
      }//--------------------------------------------------------------------



      /**
       * getGrau: Retorna o grau de um vértice em um Grafo
       * @param Vertice i
       * @return int grauVertice
       */

       int grauVertice(Vertice v)
       {
         int grauVertice = 0;
         for (int j = 0; j < numVertice; ++j)
         {
            if(isAresta(v,j))
            {
               grauVertice++;
            }
         }
         return grauVertice;
       }//--------------------------------------------------------------------


       /**
        * isSimples: 
        * @param Grafo f
        * @return true se o Grafo for simples
        * @param false
        */

        bool isSimples()
        {
            bool resp = true;
            int x = numVertice;
            for (int i = 0; i < numVertice; ++i)
            {
               if(isAresta(i,i) == NULO)
               {
                  x++;
               }
            }
            if(x == numVertice)
            {
               resp = true;
            }
            return resp;
        }//--------------------------------------------------------------------



      
         /**
          * isNulo: Método que diz se um grafo possui apenas
          * vertices isolados
          * @return true se um grafo for NULO
          */

          bool isNulo()
          {
            bool resp = true;
            for (int i = 0; i < numVertice; ++i)
            {  
               for (int j = i+1; j < numVertice; ++j)
               {
                  if(isAresta(i,j))
                  {
                     resp = false;
                     j = numVertice;
                     i = numVertice;
                  }
               }
            }
            return resp;
         }//--------------------------------------------------------------------


         /**
          * isRegular: Metodo que diz se todos os vertices de um grafo possuem
          * os mesmo grau.
          */

         bool isRegular()
         {
            bool resp = true;
            if(isNulo() == false)
            {               
               int x = grauVertice(0);
               for (int i = 0; i < numVertice; ++i)
               {
                  for (int j = 0; j < numVertice; ++j)
                  {
                     if(x != grauVertice(j))
                     {
                        resp = false;
                        i = numVertice;
                     }
                  }
               }
            }
            return resp;
         }//--------------------------------------------------------------------


         /**
          * isCompleto: Metodo que diz se todos os vertices sao adjacentes, ou seja,
          * todos os vertices estao conectados ao menos por uma aresta
          */
         bool isCompleto()
         {
            bool resp = false;
            if(isConexo())
            {
               resp = true;
               for (int i = 0; i < numVertice; ++i)
               {
                  for (int j = i+1; j < numVertice; ++j)
                  {
                     if(!isAresta(i,j))
                     {
                        resp = false;
                     }
                  }
               }
            }
            return resp;
         }//--------------------------------------------------------------------

         void inicializacoes(Vertice v, int** caminhos, int* distancia)
         {

          iniciaVisitados();         
          
           for(int i = 0; i<numVertice; ++i)
           {
              if(v == i)
              {
                 distancia[i] = 0;
              }
              if(isAresta(v,i))
              {
                 distancia[i] = getAresta(v,i);
                 caminhos[v][i]  = 1;
              }
              else if(!isAresta(v,i))
              {
                 distancia[i] = INIFITY;                
              }
           }
         }
         
         /**
          * Algoritmo de Dijkstra
          */ 
          
          void dijkstra(Vertice v)
          {
            // Vetor de distancias
            int*  distancia = new int[MAX_VERTICE];
            // Matriz de Caminhos
            int** caminhos  = new int*[MAX_VERTICE];
            for (int i = 0; i < numVertice; ++i)
              caminhos[i] = new int[MAX_VERTICE];
            // Inicializacoes necessarias  
            inicializacoes(v, caminhos, distancia);

            for (int i = 0; i < numVertice; ++i)
            {
              if(visitados[i] == false && isAresta(v,i) && getAresta(v,i) < distancia[i])
              {
                  visitados[i] = true;
                  for (int j = 0; j < numVertice; ++j)
                  {
                      if(isAresta(i,j) && visitados[j] == false && (distancia[j] + getAresta(i,j) < distancia[i]))
                      {
                        distancia[j] = distancia[i] + getAresta(i,j);
                      }
                  }
              }
            }
          
        }

         /**
          * Simulacoes de testes
          */
         void test(bool a)
         {
            if(a)
               cout << "SIM ";
            else
               cout << "NAO ";
         }


};

//--------------------------------------------------------------------
//                              Testes
//--------------------------------------------------------------------
void testes(Grafo* g)
{
      g->imprimirVerticeAresta();
      cout <<"S   R   N   C   E   U" << endl;
      g->test(g->isSimples());  
      g->test(g->isRegular());  
      g->test(g->isNulo());     
      g->test(g->isCompleto()); 
      g->test(g->isEuleriano());
      g->test(g->isUnicursal());
      cout << "\n";
}

//=====================================================================
// FUNCAO PRINCIPAL
//=====================================================================
int main(int argc, char **argv)
{

   Grafo *g = new Grafo;

   while (g->lerGrafo() == true)
   {
	   //g->imprimir();
      //g->imprimirVerticeAresta();
      //g->imprimirPendenteAndIsolado();
      testes(g);


      delete g;
      g = new Grafo;
   }
   delete g;

   return 0;
}//--------------------------------------------------------------------
