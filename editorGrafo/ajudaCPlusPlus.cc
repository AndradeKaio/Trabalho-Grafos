#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

class Grafo {
   public:
      int atributo;

      Grafo(){
         atributo = 15;
      }

      void metodo (int valor) { 
         atributo = valor; 
      }
};

int* doidao(int& pendente, int* isolado){
   pendente = 5;
   *isolado = 6;
   int* resp = new int[3];
   resp[0] = 10;
   resp[1] = 20;
   resp[2] = 30;
   return resp;
}


int main (){
   Grafo g1;
   Grafo* g2;
   Grafo g3[3];
   Grafo** g4;

   //PARA O G1
   g1.atributo = 2;
   g1.metodo(4);

   cout << "IMPRIMINDO ATRIBUTO DE G1: " << g1.atributo << endl << endl;

   //PARA G2.
   g2 = new Grafo;

   g2->atributo = 2;
   g2->metodo(4);
   
   cout << "IMPRIMINDO ATRIBUTO DE G2: " << g2->atributo << endl << endl;

   delete g2;

   g2 = new Grafo[3];

   g2[0].atributo = 2;
   g2[0].metodo(4);
   
   g2[2].atributo = 2;
   g2[2].metodo(4);

   cout << "IMPRIMINDO ATRIBUTO DE G2[0]: " << g2[0].atributo << endl;
   cout << "IMPRIMINDO ATRIBUTO DE G2[1]: " << g2[1].atributo << endl;
   cout << "IMPRIMINDO ATRIBUTO DE G2[2]: " << g2[2].atributo << endl << endl;

   delete [] g2;

   //PARA O G3
   g3[0].atributo = 2;
   g3[0].metodo(4);
   
   g3[2].atributo = 2;
   g3[2].metodo(4);

   cout << "IMPRIMINDO ATRIBUTO DE G3[0]: " << g3[0].atributo << endl;
   cout << "IMPRIMINDO ATRIBUTO DE G3[1]: " << g3[1].atributo << endl;
   cout << "IMPRIMINDO ATRIBUTO DE G3[2]: " << g3[2].atributo << endl << endl;
   
   //PARA G4
   g4 = new Grafo*[3];

   g4[0] = new Grafo;
   g4[2] = new Grafo;

   g4[0]->atributo = 2;
   g4[0]->metodo(4);
   
   g4[2]->atributo = 2;
   g4[2]->metodo(4);

   cout << "IMPRIMINDO ATRIBUTO DE G4[0]: " << g4[0]->atributo << endl;
   cout << "IMPRIMINDO ATRIBUTO DE G4[2]: " << g4[2]->atributo << endl << endl;

   delete g4[0];
   delete g4[2];

   int pendente = 10;
   int isolado = 25;

   int* vet = doidao(pendente, &isolado);

   cout << "NUMERO DE PENDENTES: " << pendente << endl;
   cout << "NUMERO DE ISOLADOS: " << isolado << endl;
   cout << "GRAU DO VERTICE [0]: " << vet[0] << endl;
   cout << "GRAU DO VERTICE [1]: " << vet[1] << endl;
   cout << "GRAU DO VERTICE [2]: " << vet[2] << endl;
}
