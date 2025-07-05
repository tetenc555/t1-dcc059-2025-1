#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {
public:
    No(char id, bool ehPondVertice);
    No(No* noOriginal);
    ~No();

    char id;
    int peso;
    vector<Aresta*> arestas;
    No(char id, int peso);
    bool visitado;
    void criaAresta(char alvo);
    void imprimeConexoes(bool ehPondAresta);

    void imprimeFormato(bool ehPondAresta);

    void setVisitado(bool visitado);

    bool getVisitado();
};



#endif //NO_H
