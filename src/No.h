#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {
public:
    No(char id, bool ehPondVertice);
    No(const No* noOriginal);
    No(char id, int peso);
    No(char id, int peso, bool isDominante);
    ~No();

    char id;
    int peso;
    bool isDominante;
    vector<Aresta*> arestas;
    bool visitado;

    void criaAresta(char alvo);
    void imprimeConexoes(bool ehPondAresta);
    void imprimeFormato(bool ehPondAresta);
    void impressaoFinal();
    void setVisitado(bool visitado);
    bool getVisitado();
};



#endif //NO_H
