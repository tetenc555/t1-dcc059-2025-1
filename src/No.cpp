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

void No::imprimeConexoes(bool ehPondAresta) {
    cout << "Conexões do Nó " << this->id ;
    int tamanho = arestas.size();
    if (tamanho == 0) {
        cout << "--" << endl;
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        cout << " -> " << arestas[i]->id_no_alvo;
        if (ehPondAresta) {
            cout << " (Peso: " << arestas[i]->peso << ")";
        }
    }
    cout << endl;
}

