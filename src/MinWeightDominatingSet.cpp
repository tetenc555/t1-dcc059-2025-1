//
// Created by Bebs Fiorillo on 26/07/25.
//

#include "MinWeightDominatingSet.h"
#include <iostream>
#include <queue>
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

void calculaPesoNoCandidatoGuloso(priority_queue<tuple<float,char>,vector<tuple<float,char>>,greater<tuple<float,char>>>* candidatos)
{
    for (int i=0; i < candidatos->size(); ++i)
    {
        tuple<float,char> noAtualizar = candidatos[0];

    }
}

void MinWeightDominatingSet::guloso(Grafo *grafoInicial)
{
    conjuntoSolucao = new Grafo(grafoInicial->in_direcionado,grafoInicial->in_ponderado_aresta,grafoInicial->in_ponderado_vertice); //declara solucao vazia
    priority_queue<tuple<float,char>,vector<tuple<float,char>>,greater<tuple<float,char>>> candidatos; //declara lista de candidatos
    for (No* no : grafoInicial->lista_adj) //adicao inicial a lista de candidatos
    {
        float pesoProcessamento=no->peso;
        pesoProcessamento=pesoProcessamento/no->arestas.size();
        candidatos.emplace(pesoProcessamento,no->id);
    }

    while (conjuntoSolucao->lista_adj.size() < grafoInicial->lista_adj.size() || !candidatos.empty())
    {

    }
}

void MinWeightDominatingSet::gulosoRand(Grafo *grafoInicial) {
    cout<< "teste guloso random" << endl;
}

void MinWeightDominatingSet::gulosoRandAdapt(Grafo *grafoInicial) {
    cout<< "teste guloso random adapt" << endl;
}





