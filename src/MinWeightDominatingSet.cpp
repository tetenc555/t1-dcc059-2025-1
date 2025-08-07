//
// Created by Bebs Fiorillo on 26/07/25.
//

#include "MinWeightDominatingSet.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cfloat>
#include <complex>
using namespace std;

MinWeightDominatingSet::MinWeightDominatingSet(Grafo* grafoInicial, int tipo) {
    if (!grafoInicial->in_ponderado_vertice){
        throw logic_error("Grafo não é vértice ponderado!");
    }
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
        No* noGrafoInicial = grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(idNoAtualizar)];
        float pesoRelativo = noGrafoInicial->peso;
        int qtdArestasValidas = 0;
            for (Aresta* aresta : noGrafoInicial->arestas)
            {
                if (!conjuntoSolucao->verificaExistenciaNo(aresta->id_no_alvo)) //verifica se a aresta se conecta a um no que ja e dominado, contando apenas elas
                    qtdArestasValidas++;
            }
            if (qtdArestasValidas != 0)
                pesoRelativo = pesoRelativo / qtdArestasValidas;
            filaAtualizada.emplace(make_tuple(pesoRelativo, idNoAtualizar));
    }
    candidatos->swap(filaAtualizada);
}

void MinWeightDominatingSet::guloso(Grafo *grafoInicial)
{
    conjuntoSolucao = new Grafo(grafoInicial->in_direcionado,grafoInicial->in_ponderado_aresta,grafoInicial->in_ponderado_vertice); //declara solucao vazia
    priority_queue<tuple<float,char>, vector<tuple<float,char>>, greater<tuple<float,char>>> candidatos; //lista de candidatos
    for (No* no : grafoInicial->lista_adj) //adicao inicial a lista de candidatos
    {
        float pesoRelativo=no->peso;
        pesoRelativo=pesoRelativo/no->arestas.size();
        candidatos.emplace(make_tuple(pesoRelativo,no->id));
    }

    // Enquanto houver candidatos disponíveis E o conjunto solução não cobrir todo o grafo
    while (!candidatos.empty() && conjuntoSolucao->lista_adj.size() < grafoInicial->lista_adj.size()) {
        // Pega o melhor candidato da lista de candidatos
        tuple<float, char> melhorCandidato = candidatos.top();
        candidatos.pop();
        // Encontra o nó correspondente no grafo original
        No* melhorCandidatoNo = grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(get<1>(melhorCandidato))];

        // INSERE O NÓ DOMINANTE NO CONJUNTO SOLUÇÃO (com 'true' indicando que é dominante)
        conjuntoSolucao->inserirNosComDominancia(melhorCandidatoNo->id, melhorCandidatoNo->peso, true);

        // Processa os vizinhos (nós dominados)
        for (Aresta* aresta : melhorCandidatoNo->arestas) {
            // Verifica se o nó alvo ainda não está no conjunto solução
            if (!conjuntoSolucao->verificaExistenciaNo(aresta->id_no_alvo)) {
                // Obtém o nó alvo a partir do grafo original
                No* noAlvo = grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(aresta->id_no_alvo)];

                // Insere o nó dominado no conjunto solução (com 'false' indicando que não é dominante)
                conjuntoSolucao->inserirNosComDominancia(noAlvo->id, noAlvo->peso, false);

                // Adiciona arestas para manter a conectividade no conjunto solução
                conjuntoSolucao->processarArestaIda(melhorCandidatoNo->id, noAlvo->id, noAlvo->peso);
                conjuntoSolucao->processarArestaVolta(noAlvo->id, melhorCandidatoNo->id, noAlvo->peso);
            }
        }
    }
}

void MinWeightDominatingSet::gulosoRand(Grafo *grafoInicial) {
    cout<< "teste guloso random" << endl;
}

void MinWeightDominatingSet::gulosoRandAdapt(Grafo *grafoInicial) {
    cout<< "teste guloso random adapt" << endl;
}

void MinWeightDominatingSet::impressao()
{
    cout << "Vértices Domintantes: " << endl;
    for (No* no : this->conjuntoSolucao->lista_adj)
    {
        if (no->isDominante)
        {
            cout << no->id << " (Peso:" << no->peso << "), ";
        }
    }
    cout << endl;
    cout << "Vértices Dominadas: " << endl;
    for (No* no : this->conjuntoSolucao->lista_adj)
    {
        if (!no->isDominante)
        {
            cout << no->id << " (Peso:" << no->peso << "), ";
        }
    }
}



