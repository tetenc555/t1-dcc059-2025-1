#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {
public:
    No(char id, bool ehPondVertice);
    ~No();

    char id;
    int peso;
    vector<Aresta*> arestas;
    No(char id, int peso);

    void criaAresta(char alvo);
    void imprimeConexoes(bool ehPondAresta);
};



#endif //NO_H
