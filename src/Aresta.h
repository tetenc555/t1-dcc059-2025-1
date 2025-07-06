#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
using namespace std;

class Aresta {
public:
    Aresta(char alvo, int peso);
    Aresta(Aresta* arestaOriginal);
    ~Aresta();

    char id_no_alvo;
    int peso;
    
};



#endif //ARESTA_H
