z/***********************************************************************
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
#define MAX_INT         		0x7FFFFFFF
#define NULO						-1
#define BRANCO						0
#define PRETO						1

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


      //--------------------------------------------------------------------
      // iniciaVisitados: Inicia o vetor de visitados como false
      //--------------------------------------------------------------------
      void iniciaVisitados()
      {
         for (int i = 0; i < numVertice; ++i)
         {
            visitados[i] = false;
         }
      }//--------------------------------------------------------------------


      //--------------------------------------------------------------------
      // pesquisaProfunda: Busca todos os vertices do grafo usando busca
      // em profundidade
      //--------------------------------------------------------------------
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


      
      //--------------------------------------------------------------------
      // pesquisaProfunda: Busca todos os vertices do grafo usando metodos
      // da profundidade
      //--------------------------------------------------------------------

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


      //--------------------------------------------------------------------
      // isConexo: Metodo que retorna true se houver pelo menos um caminho 
      // entre todos os vertices do Grafo.
      //--------------------------------------------------------------------

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
 /*
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
      * */


      
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
          * isRegular(): funcao que diz se um Digrafo é Regular
          * @return true se um digrafo for regular
          * 
          */
         bool isRegular()
         {
            bool resp = true;
            if(isNulo() == false)
            {               
               int x = getGrauEntrada(0);
               int y = getGrauSaida(0);
               for (int i = 0; i < numVertice; ++i)
               {
                  for (int j = 0; j < numVertice; ++j)
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
			  
			  for (int i = 0; i < numVertice; ++i)
               {
                  for (int j = 0; j < numVertice; ++j)
                  {
                     x += getGrauEntrada(j);
                     y += getGrauSaida(j);
                  }
               }
               return resp = (x == y) ? true: false;
		  }//--------------------------------------------------------------------
		  
		  /**
		   * isFortementeConexo: metodo que retorna um valor true se existe um caminho
		   * seguindo da direcao das arestas (dirigido) entre todos os pares de vertice
		   * @return true
		   */ 
		   bool isFortementeConexo()
		   {
			   bool resp = false;			   
			   for(int i =0; i<numVertice; ++i)
			   {
				   if(getGrauEntrada(i) < 1)
				   {
					   resp = false;
					   i = numVertice;
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
					Grafo g  = getGrafoCorp();
					if(g.isFortementeConexo)
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
			 Grafo getGrafoCorp()
			 {
				 Grafo g;
				 int temp = 0;
				 for(int i = 0; i < numVertice; i++)
				 {
					g.inserirAresta(i, i, NULO);
					for(int j = i+1; j < numVertice; j++)
					{	
						temp = getAresta(i,j);
						//cout << "Peso inserido " << temp << "\n";
						//cout << "Numero aresta "<< " " << numAresta << "\n";
						g.inserirAresta(i, j, temp);
						g.inserirAresta(j, i, temp);
					}
				}		 
				 return g;
			 }
				
		   
		  


         //--------------------------------------------------------------------
         // isCompleto: Metodo que diz se todos os vertices sao adjacentes
         //--------------------------------------------------------------------

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
         }//-------------------  -------------------------------------------------

         //--------------------------------------------------------------------
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
     // g->test(g->isEuleriano());
     // g->test(g->isUnicursal());
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
