//
// Created by Bebs Fiorillo on 26/07/25.
//

#include "MinWeightDominatingSet.h"
#include <iostream>
using namespace std;

MinWeightDominatingSet::MinWeightDominatingSet(Grafo* grafoInicial, int tipo) {
    switch (tipo) {
        case 0: {
            this->guloso(grafoInicial);
            break;
        }
        case 1: {
            this->gulosoRand(grafoInicial);
            break;
        }
        case 2: {
            this->gulosoRandAdapt(grafoInicial);
            break;
        }
        default: {
            throw logic_error("Tipo de construtor inválido!");
        }
    }
}

MinWeightDominatingSet::~MinWeightDominatingSet() {
    delete conjuntoSolucao;
}

void MinWeightDominatingSet::guloso(Grafo *grafoInicial) {
    cout<< "teste guloso" << endl;
}

void MinWeightDominatingSet::gulosoRand(Grafo *grafoInicial) {
    cout<< "teste guloso random" << endl;
}

void MinWeightDominatingSet::gulosoRandAdapt(Grafo *grafoInicial) {
    cout<< "teste guloso random adapt" << endl;
}





