//
// Created by Bebs Fiorillo on 26/07/25.
//

#include "MinWeightDominatingSet.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <complex>
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

void reCalculaPesoNoCandidatoGuloso(priority_queue<tuple<float,char>,vector<tuple<float,char>>,greater<tuple<float,char>>>* candidatos, Grafo* conjuntoSolucao, Grafo* grafoInicial)
{
    priority_queue<tuple<float,char>,vector<tuple<float,char>>,greater<tuple<float,char>>> filaAtualizada;
    while (!candidatos->empty())
    {
        tuple<float,char> noAtualizar = candidatos->top();
        char idNoAtualizar = get<1>(noAtualizar);
        candidatos->pop();
        if (!conjuntoSolucao->verificaExistenciaNo(idNoAtualizar))
        {
            No* noGrafoInicial = grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(idNoAtualizar)];
            float pesoProcessamento = noGrafoInicial->peso;
            int qtdArestasValidas = 0;
            for (Aresta* aresta : noGrafoInicial->arestas)
            {
                if (!conjuntoSolucao->verificaExistenciaNo(aresta->id_no_alvo))
                    qtdArestasValidas++;
            }
            if (qtdArestasValidas != 0)
                pesoProcessamento = pesoProcessamento / noGrafoInicial->arestas.size();
            filaAtualizada.emplace(make_tuple(pesoProcessamento, idNoAtualizar));
        }
    }
    candidatos->swap(filaAtualizada);
}

void MinWeightDominatingSet::guloso(Grafo *grafoInicial)
{
    conjuntoSolucao = new Grafo(grafoInicial->in_direcionado,grafoInicial->in_ponderado_aresta,grafoInicial->in_ponderado_vertice); //declara solucao vazia
    priority_queue<tuple<float,char>, vector<float,char>, greater<tuple<float,char>>> candidatos; //lista de candidatos
    for (No* no : grafoInicial->lista_adj) //adicao inicial a lista de candidatos
    {
        float pesoProcessamento=no->peso;
        pesoProcessamento=pesoProcessamento/no->arestas.size();
        candidatos.emplace(make_tuple(pesoProcessamento,no->id));
    }

    while (conjuntoSolucao->lista_adj.size() < grafoInicial->lista_adj.size() || !candidatos.empty())
    {
        tuple<float,char> melhorCandidato = candidatos.top();
        candidatos.pop();
        No* melhorCandidatoNo = new No(grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(get<1>(melhorCandidato))]);
        melhorCandidatoNo->isDominante = true;
        for (Aresta* aresta : melhorCandidatoNo->arestas)
        {
            if (!conjuntoSolucao->verificaExistenciaNo(aresta->id_no_alvo))
            {
                No* noAlvo = new No(grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(aresta->id_no_alvo)]);
                noAlvo->isDominante =false;
                conjuntoSolucao->inserirNos(noAlvo->id,noAlvo->peso);
                conjuntoSolucao->processarArestaIda(melhorCandidatoNo->id,noAlvo->id,noAlvo->peso);
                conjuntoSolucao->processarArestaVolta(noAlvo->id,melhorCandidatoNo->id,noAlvo->peso);
            }
        }
        reCalculaPesoNoCandidatoGuloso(candidatos, conjuntoSolucao, grafoInicial);
    }
}

void MinWeightDominatingSet::gulosoRand(Grafo *grafoInicial) {
    cout<< "teste guloso random" << endl;
}

void MinWeightDominatingSet::gulosoRandAdapt(Grafo *grafoInicial) {
    cout<< "teste guloso random adapt" << endl;
}





