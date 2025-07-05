#include "No.h"

#include <iostream>

No::No(char id, int peso) {
    if (peso == -1) {
        this->id=id;
        this->peso=0;
        this->visitado=false;
    }
    else {
        this->id=id;
        this->peso=peso;
        this->visitado=false;
    }
}

No::No(No* noOriginal) {
    if (noOriginal->peso == -1) {
        this->id=noOriginal->id;
        this->peso=0;
        this->visitado=false;
    }
    else {
        this->id=noOriginal->id;
        this->peso=noOriginal->peso;
        this->visitado=false;
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

void No::imprimeFormato(bool ehPondAresta) {
    cout << this->id;
    int tamanho = arestas.size();
    if (ehPondAresta) {
        cout << " (" << this->peso << ")";
    }
    if (tamanho == 0) {
        cout << " -- " << endl;
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        cout << " -> " << arestas[i]->id_no_alvo;
        if (ehPondAresta) {
            cout << " (" << arestas[i]->peso << ")";
        }
    }
    cout << endl;
}

void No::setVisitado(bool visitado) {
    this->visitado=visitado;
}

bool No::getVisitado() {
    return this->visitado;
}

