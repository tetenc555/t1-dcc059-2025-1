//
// Created by Bebs Fiorillo on 26/07/25.
//

#ifndef MINWEIGHTDOMINATINGSET_H
#define MINWEIGHTDOMINATINGSET_H
#include <iostream>

#include "Grafo.h"
using namespace std;
class MinWeightDominatingSet {

public:
    Grafo* conjuntoSolucao;

    MinWeightDominatingSet(Grafo* grafoInicial, int tipo);
    ~MinWeightDominatingSet();
    void guloso(Grafo* grafoInicial);
    void gulosoRand(Grafo* grafoInicial);
    void gulosoRandAdapt(Grafo* grafoInicial);
};

#endif //MINWEIGHTDOMINATINGSET_H