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

    MinWeightDominatingSet(Grafo *grafoInicial, int tipo, float alpha);

    ~MinWeightDominatingSet();
    void guloso(Grafo* grafoInicial);
    void gulosoRand(Grafo *grafoInicial, float alpha);
    void gulosoRandAdapt(Grafo* grafoInicial);
    void impressao();
};

#endif //MINWEIGHTDOMINATINGSET_H