#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {
public:
    No(int peso, char id, bool ehPondVertice);
    ~No();

    char id;
    int peso;
    vector<Aresta*> arestas;
    void criaAresta();
};



#endif //NO_H
