#include "Aresta.h"

Aresta::Aresta(char alvo, int peso) {
    this->id_no_alvo = alvo;
    this->peso = peso;
}

Aresta::Aresta(Aresta *arestaOriginal) {
    this->id_no_alvo = arestaOriginal->id_no_alvo;
    this->peso = arestaOriginal->peso;
}

