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
#include <err.h>

using namespace std;


//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_VERTICE       500
#define MAX_INT           0x7FFFFFFF
#define NULO              -1
#define BRANCO            0
#define PRETO             1
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

   /**
 * Lista simples dinamica
 * @author Max do Val Machado
 * @version 2 01/2015
 */
class Lista
{

   public:
      int numElementos;
   public:

   //TIPO CELULA ===================================================================
   typedef struct Celula 
   {
       Vertice elemento;
       struct Celula *prox; // Aponta a celula prox.
   } Celula;
    
   Celula *novaCelula(Vertice elemento) 
   {
      Celula *nova = (Celula*) malloc(sizeof(Celula));
      nova->elemento = elemento;
      nova->prox     = NULL;
      return nova;
   }
    
   //LISTA PROPRIAMENTE DITA =======================================================
   Celula *primeiro, *ultimo;
    
    
   /**
    * Cria uma lista sem elementos (somente no cabeca).
    */

   void start () 
   {
      numElementos = 0;
      primeiro = novaCelula(-999);
      ultimo = primeiro;
   }
  
   /**
    * Insere um elemento na ultima posicao da lista.
    * @param x int elemento a ser inserido.
    */
   void inserirFim(Vertice v2) 
   {
      int tam = numElementos;
      ultimo->prox = novaCelula(v2);
      ultimo = ultimo->prox;
      numElementos++;
   }

   /**
    * Busca na lista o Peso de um determinado vertice
    * retorna o mesmo se for diferente de NULO 
    */

    Peso getVerticePeso(Vertice v2)
    {
      int tam = numElementos;
      Peso resp;
      if (primeiro == ultimo)
      {
         errx(1, "Erro ao remover (vazia)!");
      } 
      else if(v2 < 0 || v2 >= tam)
      {
         errx(1, "Erro ao remover posicao (%d/ tamanho = %d) invalida!", v2, tam);
      } 
      else 
      {
         // Caminhar ate a posicao anterior a insercao
         Celula *i = primeiro;
         int j;
         for(j = 0; j < v2; j++, i = i->prox);
         

         Celula *tmp = i->prox;
         //resp = tmp->peso;

         i = tmp = NULL;
      }
      return resp;
    }
    
   /**
    * Calcula e retorna o tamanho, em numero de elementos, da lista.
    * @return resp int tamanho
    */
   int tamanho() 
   {
      return numElementos;
   }
    

    
    
   /**
    * Mostra os elementos da lista separados por espacos.
    */
   void mostrar() 
   {

      Celula *i;
      printf("[");
      for (i = primeiro->prox; i != NULL; i = i->prox) 
      {
         printf(" %d", i->elemento);
      }
      printf(" ]");
      //printf("\n");
   }
    
    /**
     * Percorre a lista contando a quantidade de nodos contidos nela
     */

    int contarElementos() 
    {

      Celula *i;
      int contador = 0;
      for (i = primeiro->prox; i != NULL; i = i->prox) 
      {
         contador++;
      }
      return contador;
   }
   /**
    * Procura um elemento e retorna se ele existe.
    * @param x Elemento a pesquisar.
    * @return <code>true</code> se o elemento existir,
    * <code>false</code> em caso contrario.
    */
   bool pesquisar(Vertice x) 
   {
      bool retorno = false;
      Celula *i;
      int y = 0;
      for (i = primeiro->prox; i != NULL; i = i->prox) 
      {
         if(i->elemento == x && i->elemento != NULO)
         {
            retorno = true;

            i = ultimo;
         }
      }
      return retorno;
   }

}; //------------------------------------------------------------------------------


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

      Lista caminhos[MAX_VERTICE];
      

          
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
         iniciaTabela(temp);

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

      /**
       * iniciaTabela: Metodo que inicia a tabela de Lista
       * com valores nulos
       */
      void iniciaTabela(int quantidade)
      {
         for (int i = 0; i < quantidade; ++i)
         {

            caminhos[i].start();
         }
      }


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


        void inicializacoes(Vertice v, int* distancia)
         {

          iniciaVisitados();     
          
           for(int i = 0; i<numVertice; ++i)
           {
              if(v == i)
              {
                 distancia[v] = 0;
                 caminhos[v].inserirFim(0);
              }              
              else if(isAresta(v,i) && i!=v)
              {
                cout << i;
                distancia[i] = getAresta(v,i);
                for (int x = 0; x <= i; ++x)
                {
                  caminhos[i].inserirFim(x);
                }
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
            int*  distancia = new int[numVertice];

            // Inicializacoes necessarias  
            inicializacoes(v,distancia);
            visitados[v] = true;
            if( getGrauSaida(v) > 0)
            {
              for (int i = 0; i < numVertice; ++i)
              {
                if(visitados[i] == false && isAresta(v,i) && getAresta(v,i) <= distancia[i])
                {

                  visitados[i] = true;
                  for (int j = 0; j < numVertice; ++j)
                  {
                    if(isAresta(i,j) && visitados[j] == false && (distancia[i] + getAresta(i,j) < distancia[j]))
                    { 
                      //cout << i<< j<<endl;         
                      //distancia[j] = distancia[i] + getAresta(i,j); 
                      //caminhos[j]  = caminhos[i];
                      //caminhos[j].inserirFim(j,getAresta(i,j));
                    }
                  }
                }
              }
            }
            else
            {
              caminhos[0].inserirFim(0);
              for (int i = 1; i < numVertice; ++i)
              {
                caminhos[i].inserirFim(NULO);
              }
            }
            mostrarCaminhos(0, distancia);            
          }


          /**
           *
           */
          void mostrarCaminhos(Vertice v, int * distancia)
          {
            for (int i = 0; i < numVertice; ++i)
            {
              cout << "Distancia do vertice inicial para o vertice ("<<i;
              cout << ") = "; caminhos[i].mostrar();
              cout << distancia[i];
              cout << endl; 
            }
          }


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
        g->dijkstra(0);
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
