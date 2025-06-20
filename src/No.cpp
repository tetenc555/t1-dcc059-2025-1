#include "No.h"

No::No(int peso, char id, bool ehPondVertice) {
    this->id=id;
    if (ehPondVertice) {
        this->peso=peso;
    }
}

void No::criaAresta() {

}

