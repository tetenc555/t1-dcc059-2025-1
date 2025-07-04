#include "No.h"

#include <iostream>

No::No(char id, int peso) {
    if (peso == -1) {
        this->id=id;
        this->peso=0;
    }
    else {
        this->id=id;
        this->peso=peso;
    }
}

void No::criaAresta(char alvo) {
    Aresta* addAresta = new Aresta(alvo, -1);
    arestas.push_back(addAresta);
}

void No::imprimeConexoes(bool ehPondAresta) {
    cout << "Conexões do Nó " << this->id ;
    int tamanho = arestas.size();
    if (ehPondAresta) {
        cout << " (Peso: " << this->peso << ")";
    }
    if (tamanho == 0) {
        cout << " -- " << endl;
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

