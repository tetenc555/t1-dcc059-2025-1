#include "No.h"

#include <iostream>

No::No(char id, int peso) {
    if (peso == -1) {
        this->id=id;
        this->peso=0;
        this->visitado=false;
        this->isDominante=false;
    }
    else {
        this->id=id;
        this->peso=peso;
        this->visitado=false;
        this->isDominante=false;
    }
}

No::No(char id, int peso, bool isDominante) {
    if (peso == -1) {
        this->id=id;
        this->peso=0;
        this->visitado=false;
        this->isDominante=isDominante;
    }
    else {
        this->id=id;
        this->peso=peso;
        this->visitado=false;
        this->isDominante=false;
    }
}

No::No(const No* noOriginal) {
    if (noOriginal->peso == -1) {
        this->id=noOriginal->id;
        this->peso=0;
        this->visitado=false;
        this->isDominante=noOriginal->isDominante;
    }
    else {
        this->id=noOriginal->id;
        this->peso=noOriginal->peso;
        this->visitado=false;
        this->isDominante=noOriginal->isDominante;
    }
    for (Aresta* a : noOriginal->arestas) {
        this->arestas.push_back(new Aresta(a));
    }
}

No::~No() {
    for (Aresta* a : arestas) {
        delete a;
    }
}


void No::criaAresta(char alvo) {
    auto* addAresta = new Aresta(alvo, -1);
    arestas.push_back(addAresta);
}

void No::imprimeConexoes(bool ehPondAresta) {
    cout << "Conexões do Nó " << this->id ;
    int tamanho = int(arestas.size());
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
    int tamanho = int(arestas.size());
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

void No::impressaoFinal() {
    cout << this->id << ": ";
    int tamanho = arestas.size();
    if (tamanho == 0) {
        cout << "-- " << endl;
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        if (i != 0) {
            cout << " -> ";
        }
        cout << arestas[i]->id_no_alvo;
    }
    cout << endl;
}

void No::setVisitado(bool visitado) {
    this->visitado=visitado;
}

bool No::getVisitado() {
    return this->visitado;
    cout << "hello world" << endl;

}


