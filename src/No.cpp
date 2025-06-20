#include "No.h"

#include <iostream>

No::No(char id, bool ehPondVertice) {
    this->id=id;
    this->peso=0;
    if (ehPondVertice) {
        cin>> this->peso;
    }
}

void No::criaAresta(char alvo, bool ehPondVertice) {
    int peso=0;
    if (ehPondVertice) {
        cin>> peso;
    }
    Aresta* addAresta = new Aresta(alvo, peso);
    arestas.push_back(addAresta);
}

