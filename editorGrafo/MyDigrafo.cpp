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
      int caminho;
      

          
   public:
      //--------------------------------------------------------------------
      // Construtor
      //--------------------------------------------------------------------
      Grafo()
      {
         numVertice     = 0;
         numAresta      = 0;
         componentes    = 0;
         caminho        = 0;
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
            for(int j = 0; j < numVertice; j++)
            {	
               cin >> temp;
               //cout << "Peso inserido " << temp << "\n";
               //cout << "Numero aresta "<< " " << numAresta << "\n";
               inserirAresta(i, j, temp);            
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
            if(peso != NULO)
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
          iniciaVisitados();
          for (int i = 0; i < numVertice; ++i)
            {
               if(visitados[i] == false && getGrauSaida(i) >= 1)
               {
                  componentes++;
                  caminho++;
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
               if(isAresta(v,i) && visitados[i] == false && getGrauEntrada(i)>=1 && getGrauSaida(i)>=1)
               {
                  caminho++;
                  visite(i);
               }              
            }
      }//--------------------------------------------------------------------

      /**
       * pesquisaLargura: Algoritmo de caminhamento em Digrafo utilizando o metodo
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
       * isConexo: Metodo que retorna verdadeiro se houver ao menos um caminho
       * entre todos os vertices do grafo.
       */
      bool isConexo()
      {
         bool resp = false;
         pesquisaProfundidade();
         if(componentes == 1)
         {
            resp = true;
         }
         return resp;
      }

      /**
       * isConexo: Metodo que retorna verdadeiro se houver ao menos um caminho
       * entre todos os vertices do Digrafo.
       */
      bool isConexo(Grafo *g)
      {
         bool resp = false;
         g->pesquisaProfundidade(g);
         if(g->componentes == 1)
         {
            resp = true;
         }
         return resp;
      }//--------------------------------------------------------------------

      /**
       * pesquisaProfundidade: Algoritmo de caminhamento em Digrafo utilizando o metodo
       * de Busca em Profundidade.
       */
      void pesquisaProfundidade(Grafo *g)
      {
          g->iniciaVisitados();
          for (int i = 0; i < numVertice; ++i)
            {
               if(g->visitados[i] == false)
               {
                  g->componentes++;
                  g->visite(i,g);
               }
            }
      }//--------------------------------------------------------------------


      //--------------------------------------------------------------------
      // visite: Visita os vinhos de um vertice nao visitado na matriz
      //--------------------------------------------------------------------
      void visite(Vertice v, Grafo *g)
      {
            g->visitados[v] = true;
            for( int i = 0; i < numVertice; i++)
            {

               if(g->isAresta(v,i)  && g->visitados[i] == false)
               {
                  g->visite(i,g);
               }
            }
      }//--------------------------------------------------------------------



      /**
       * isEuleriano: Método que verifica se um determinado Grafo é Euleriano
       * @return true caso seja Euleriano 
       * @param Grafo f
       */

      bool isEuleriano()
      {
         bool resp = false;
         if(isConexo() && !isNulo())
         {
            resp = true;
            for (int i = 1; i < numVertice; ++i)
            {
               if( (getGrauEntrada(i)+ getGrauSaida(i)) % 2 != 0)
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
          * isNulo: Método que diz se um grafo possui apenas
          * vertices isolados
          * @return true se um grafo for NULO
          */

          bool isNulo()
          {
            bool resp = true;
            for (int i = 0; i < numVertice; ++i)
            {  
               for (int j = 0; j < numVertice; ++j)
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
         /**
          * isRegular(): funcao que diz se um Digrafo é Regular
          * @return true se um digrafo for regular
          * 
          */
         bool isRegular()
         {
            bool resp = false;
            if(isNulo() == false)
            {               
               int x = getGrauEntrada(0);
               int y = getGrauSaida(0);
               resp = true;
               for (int i = 0; i < numVertice; ++i)
               {
                  for (int j = 1; j < numVertice; ++j)
                  {
                     if(x != getGrauEntrada(j) || y!= getGrauSaida(j))
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
          * isBalanceado: metodo que retorna true caso a soma do grau de entrada
          * e saida do digrafo sejam iguais
          * @return true digrafo balanceado
          */
        bool isBalanceado()
        {
          bool resp = false;
          int x = 0, y = 0;
          if(isNulo()== false)
          {
            resp = true;
            for (int i = 0; i < numVertice; ++i)
            {
              if(getGrauEntrada(i)!= getGrauSaida(i))
              {
                resp = false;
                i = numVertice;
              }
            }
          }
            //cout<<"x = "<< x << " y = "<< y << endl;
            return resp;
      }//--------------------------------------------------------------------

      /**
       * getGrauEntrada: Retorna o grau de entrada de um vertice
       * contido em um digrafo.
       * @param Vertice v
       * @return grau entrada do vertice
       */
       
       int getGrauEntrada(Vertice v)
       {
         int grauVertice = 0;
         for (int j = 0; j < numVertice; ++j)
         {
            if(isAresta(j,v))
            {
               grauVertice++;
            }
         }
         //cout<<"ENTADA->"<<grauVertice<<endl;
         return grauVertice;
       }//--------------------------------------------------------------------

      /**
       * getGrauSaida: Retorna o grau de saida de um vertice
       * contido em um digrafo.
       * @param Vertice v
       * @return grau saida do vertice
       */
    
       int getGrauSaida(Vertice v)
       {
         int grauVertice = 0;
         for (int j = 0; j < numVertice; ++j)
         {
            if(isAresta(v,j))
            {
               grauVertice++;
            }
         }
         //cout<<"SAIDA->"<<grauVertice<<endl;
         return grauVertice;
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
       * isFortementeConexo: metodo que retorna um valor true se existe um caminho
       * seguindo a direcao das arestas (dirigido) entre todos os pares de vertice
       * @return true
       */ 
      bool isFortementeConexo()
      {
        bool resp = true;
        for (int i = 0; i < numVertice; ++i)
        {
            if(getGrauSaida(i) < 1 || getGrauEntrada(i) < 1)
            {
              resp = false;
            }
        }
        return resp;
      }//--------------------------------------------------------------------
       
       /**
        * isFracamenteConexo: metodo que retorna true se um digrafo nao for fortemente
        * conexo mas seu grafoCorrespondente é conexo
        * @return true se um digrafo for fortemente conexo
        */ 
        bool isFracamenteConexo()
        {
          bool resp = false;
          if(!isFortementeConexo())
          {
              Grafo *g = getGrafoCorrespondente();
              if(g->isConexo(g))
              {
                resp = true;
              }
          }
          return resp;
      }//--------------------------------------------------------------------      
      
      /**
       * getGrafoCor: metodo que recebe um digrafo como para parametro
       * e retorna um grafo correspondente a esse digrafo, ou seja
       * sem a orientacao das arestas.
       * @param  Digrafo d
       * @return Grago g
       */
       Grafo* getGrafoCorrespondente()
       {
         int x = getNumVertice();
         int y[MAX_VERTICE][MAX_VERTICE];
         for (int i = 0; i < numVertice; ++i)
           {
             y[i][i] = NULO;
             for (int j = 0; j < numVertice; ++j)
             {
               if(isAresta(i,j))
               {
                  y[i][j] = getAresta(i,j);
                  y[j][i] = getAresta(i,j);
               }
               else
               {
                y[i][j] = -1;                
               }
             }
           }

          Grafo *g = new Grafo;
          g->excluirTodasArestas();
          g->setNumVertice(numVertice);
          for (int i = 0; i < numVertice; ++i)
           {
               g->inserirAresta(i,i,NULO);
               for (int j = 0; j < numVertice; ++j)
               {
                  g->inserirAresta(i,j,y[i][j]);
               }
           }
         return g;
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
          * Simulacoes e testes
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
      //g->imprimirVerticeAresta();
      //g->imprimir();
      //cout <<"R   B   FO   FA   E" << endl;
      g->test(g->isRegular());
      g->test(g->isBalanceado());
      g->test(g->isFortementeConexo());
      g->test(g->isFracamenteConexo());
      g->test(g->isEuleriano());
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
      //g->imprimirVerticeAresta();
      //g->imprimirPendenteAndIsolado();
      testes(g);


      delete g;
      g = new Grafo;
   }
   delete g;

   return 0;
}//--------------------------------------------------------------------
