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
#include <stdlib.h>
#include <err.h>

using namespace std;


//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_VERTICE		 		500
#define MAX_INT         		0x7FFFFFFF
#define NULO						-1
#define BRANCO						0
#define PRETO						1
#define bool   short
#define true   1
#define false  0


//=====================================================================
// DEFINICAO DE TIPOS
//=====================================================================
typedef short boolean;

typedef int Vertice;
typedef int Peso;

struct Aresta
{
  Vertice vi, vj;
  Peso peso;
};





/**
 * Lista dinamica
 * @author Max do Val Machado
 * @version 2 01/2015
 */

class Lista
{

   public:
      int numElementos;


   /**
 * Lista simples dinamica
 * @author Max do Val Machado
 * @version 2 01/2015
 */

   public:



 
   //TIPO CELULA ===================================================================
   typedef struct Celula 
   {
       Vertice elemento;
       Peso    peso;        // Elemento inserido na celula.
       struct Celula *prox; // Aponta a celula prox.
   } Celula;
    
   Celula *novaCelula(Vertice elemento, Peso peso) 
   {
      Celula *nova = (Celula*) malloc(sizeof(Celula));
      nova->elemento = elemento;
      nova->peso     = peso;
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
      primeiro = novaCelula(-999,-999);
      ultimo = primeiro;
   }
    
    
   /**
    * Insere um elemento na primeira posicao da lista.
    * @param x int elemento a ser inserido.
    */
   void inserirInicio(Vertice v2, Peso p) 
   {
      int tam = numElementos;
      //cout<< "InserirInicio tam = "<<tam << " v2 = "<< v2 << "peso = "<<p<<endl;
      Celula *tmp = novaCelula(v2, p);
      tmp->prox = primeiro->prox;
      primeiro->prox = tmp;
      if (primeiro == ultimo) 
      {                    
         ultimo = tmp;
      }
      numElementos++;
      tmp = NULL;
   }
    
   /**
    * Insere um elemento na ultima posicao da lista.
    * @param x int elemento a ser inserido.
    */
   void inserirFim(Vertice v2, Peso p) 
   {
      int tam = numElementos;
      //cout<< "InserirFim tam = "<<tam << " v2 = "<< v2 << "peso = "<<p<<endl;
      ultimo->prox = novaCelula(v2, p);
      ultimo = ultimo->prox;
      numElementos++;
   }
   /**
    * Insere um elemento em uma posicao especifica considerando que o 
    * primeiro elemento valido esta na posicao 0.
    * @param x int elemento a ser inserido.
    * @param pos int posicao da insercao.
    * @throws Exception Se <code>posicao</code> invalida.
    */
   void inserirMeio(Vertice v2, Peso peso) 
   {
    
      int tam = numElementos;
      //cout<< "InserirMeio  tam = "<<tam << " v2 = "<< v2 << "peso = "<<peso<<endl;
    
      if(v2 < 0 || v2 > tam)
      {
         errx(1, "Erro ao inserir posicao (%d/ tamanho = %d) invalida!", v2, tam);
      } 
      else if (tam == 0)
      {
         inserirInicio(v2,peso);
      } 
      else if (v2 == tam)
      {
         inserirFim(v2,peso);
      } 
      else 
      {
         // Caminhar ate a posicao anterior a insercao
        cout<<"HI";
         int j;
         Celula *i = primeiro;
         for(j = 0; j < v2; j++, i = i->prox);
    
         Celula *tmp = novaCelula(v2,peso);
         tmp->prox = i->prox;
         i->prox = tmp;
         tmp = i = NULL;
         numElementos++;
      }
   }
    
    


   /**
    * Busca na lista o Peso de um determinado vertice
    * retorna o mesmo se for diferente de NULO 
    */

    Peso getVerticePeso(Vertice v2)
    {
      Peso resp;
      int tam = numElementos;
    
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
         resp = tmp->peso;

         i = tmp = NULL;
      }
      return resp;
    }
    
    
   /**
    * Remove um elemento da primeira posicao da lista.
    * @return resp int elemento a ser removido.
    * @throws Exception Se a lista nao contiver elementos.
    */
   int removerInicio() 
   {
      if (primeiro == ultimo) 
      {
         errx(1, "Erro ao remover!");
      }
    
      Celula *tmp = primeiro;
      primeiro = primeiro->prox;
      int resp = primeiro->elemento;
      tmp->prox = NULL;
      free(tmp);
      tmp = NULL;
      numElementos--;
      return resp;
   }
    
    
   /**
    * Remove um elemento da ultima posicao da lista.
    * @return resp int elemento a ser removido.
    */
   int removerFim() 
   {
      if (primeiro == ultimo) {
         errx(1, "Erro ao remover!");
      } 
    
      // Caminhar ate a penultima celula:
      Celula *i;
      for(i = primeiro; i->prox != ultimo; i = i->prox);
    
      int resp = ultimo->elemento;
      ultimo = i;
      free(ultimo->prox);
      i = ultimo->prox = NULL;
      numElementos--;
    
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
    * Remove um elemento de uma posicao especifica da lista
    * considerando que o primeiro elemento valido esta na posicao 0.
    * @param posicao Meio da remocao.
    * @return resp int elemento a ser removido.
    * @throws Exception Se <code>posicao</code> invalida.
    */
   int removerMeio(Vertice pos) 
   {
      int resp;
      int tam = tamanho();
    
      if (primeiro == ultimo)
      {
         errx(1, "Erro ao remover (vazia)!");
      } 
      else if(pos < 0 || pos >= tam)
      {
         errx(1, "Erro ao remover posicao (%d/ tamanho = %d) invalida!", pos, tam);
      } 
      else if (pos == 0)
      {
         resp = removerInicio();
      } 
      else if (pos == tam - 1)
      {
         resp = removerFim();
      } 
      else 
      {
         // Caminhar ate a posicao anterior a insercao
         Celula *i = primeiro;
         int j;
         for(j = 0; j < pos; j++, i = i->prox);
    
         Celula *tmp = i->prox;
         resp = tmp->elemento;
         i->prox = tmp->prox;
         tmp->prox = NULL;
         free(tmp);
         i = tmp = NULL;
         numElementos--;
      }
      return resp;
   }
    
    
   /**
    * Mostra os elementos da lista separados por espacos.
    */
   void mostrar() 
   {
      printf("[ ");
      Celula *i;
      for (i = primeiro->prox; i != NULL; i = i->prox) {
         printf("%d ", i->elemento);
      }
      printf("] \n");
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

      Lista tabela[MAX_VERTICE];
      
          
   public:
      //--------------------------------------------------------------------
      // Construtor
      //--------------------------------------------------------------------
      Grafo()
      {
         numVertice = 0;
         componentes = 0;
         excluirTodasArestas();
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // Destrutor
      //--------------------------------------------------------------------
      ~Grafo()
      {
          
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // iniciaTabela: Inicia a tabela de lista com ponterios inicio
      //--------------------------------------------------------------------
      void iniciaTabela(int quantidade)
      {
         for (int i = 0; i < quantidade; ++i)
         {

            tabela[i].start();
         }
      }



      //--------------------------------------------------------------------
      // lerGrafo: Realiza a leitura do grafo no arquivo.
      //--------------------------------------------------------------------
      bool lerGrafo()
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
            //inserirAresta(i, i, NULO);
            for(int j = i+1; j < numVertice; j++)
            {	
               cin >> temp;
               //cout << "Aresta lida = " << temp << "\n";
               //cout << " "<< " " << numAresta << "\n";
               if(i != j )
                 inserirAresta(i, j, temp);
                 inserirAresta(j, i, temp);
            }
         }
         return resp;
      }//-------------------------------------------------------------------



   private:

      //--------------------------------------------------------------------
      // inserirAresta: Insere uma nova aresta.
      //--------------------------------------------------------------------
      void inserirAresta(Vertice v1, Vertice v2, Peso peso)
      {

         if(v1 > MAX_VERTICE)
         {
            printf("ERRO! Vertice %i nao existe no grafo", v1);
            return;
         }

         if(v2 > MAX_VERTICE)
         {
            printf("ERRO! Vertice %i nao existe no grafo", v2);
            return;
         }

         else if(peso != NULO)
         {
            tabela[v1].inserirFim(v2, peso);
            if(peso != NULO && !tabela[v2].pesquisar(v1))
              numAresta++;            
         }      
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // isAresta: Retorna true se existe a aresta.
      //--------------------------------------------------------------------
      boolean isAresta(Vertice v1, Vertice v2)
      {
         return tabela[v1].pesquisar(v2);
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // getAresta: Retorna o peso da aresta.
      //--------------------------------------------------------------------
      Peso getAresta(Vertice v1, Vertice v2)
      {
         return tabela[v1].getVerticePeso(v2);
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

         if(tabela[v1].primeiro == tabela[v2].ultimo)
         {
            if(tabela[v1].pesquisar(v2))
            {
               int x = tabela[v1].removerMeio(v2);
               numAresta--;
            }
            else
            {
               cout << "FILA VAZIA" << endl;
            }
         }      
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // excluirTodasArestas: Exclui todas as arestas.
      //--------------------------------------------------------------------
      void excluirTodasArestas()
      {
         for(int i = 0; i < MAX_VERTICE; i++)
         {
             Lista f;

             tabela[i] = f;
             tabela[i].start(); 
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
          iniciaVisitados();
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
               componentes++;
               visite(i);
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

         int inicioLista = 0;
         int finalLista  = 0;

         iniciaVisitados();
         
         for (int i = 0; i < numVertice; ++i)
         {
            if(visitados[i] == false)
            {
               componentes++;
               pesquisaLargura(i, &inicioLista, &finalLista);
            }
         }

      }

      void pesquisaLargura(Vertice v, int* inicioLista, int* finalLista)
      {
         for (int i = 0; i < numVertice; ++i)
         {
            if(isAresta(v,i) && visitados[v] == false)
            {
               visitados[i] = true;
               fila[*finalLista] = i;
               *finalLista++;
            }
         }

         if( fila[*inicioLista] != NULO && *finalLista != *inicioLista)
         {
            int x = fila[*inicioLista];
            *inicioLista++;
            pesquisaLargura(x, inicioLista, finalLista);
         }
         else
         {
            cout << "ERRO! Lista vazia!";
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

      bool isEuleriano()
      {
         bool resp = false;
         if(isConexo() && !isNulo())
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
            if( x % 2 == 0 )
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
            //cout<<grauVertice<<endl;        
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
            if(isConexo() && isNulo() == false)
            {
               resp = true;
               for (int i = 0; i < numVertice; ++i)
               {
                  for (int j = i+1; j < numVertice; ++j)
                  {
                     if(isAresta(i,j) == false || isAresta(j,i) == false )
                     {
                        resp = false;
                     }
                  }
               }
            }
            return resp;
         }//--------------------------------------------------------------------

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
      //cout <<"S   R   N   C   E   U" << endl;
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
