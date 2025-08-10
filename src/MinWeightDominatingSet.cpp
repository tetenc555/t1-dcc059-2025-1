//
// Created by Bebs Fiorillo on 26/07/25.
//

#include "MinWeightDominatingSet.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cfloat>
#include <complex>
#include <vector>
#include <cstdlib>
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
        case 2: {
            this->gulosoRandAdapt(grafoInicial);
            break;
        }
        default: {
            throw logic_error("Tipo de construtor inválido!");
        }
    }
}

//Cria novo construtor pro randomizado
MinWeightDominatingSet::MinWeightDominatingSet(Grafo* grafoInicial, int tipo, float alpha) {
    if (!grafoInicial->in_ponderado_vertice){
        throw logic_error("Grafo não é vértice ponderado!");
    }
    switch (tipo) {
        case 0: {
            this->guloso(grafoInicial);
            break;
        }
        case 1: {
            this->gulosoRand(grafoInicial, alpha);
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

void MinWeightDominatingSet::gulosoRand(Grafo *grafoInicial, float alpha) {
    if (alpha < 0 || alpha > 1) {
        throw invalid_argument("Alpha deve estar entre 0 e 1");
    }

    conjuntoSolucao = new Grafo(grafoInicial->in_direcionado, grafoInicial->in_ponderado_aresta, grafoInicial->in_ponderado_vertice);
    priority_queue<tuple<float, char>, vector<tuple<float, char>>, greater<tuple<float, char>>> Listacandidatos;

    // Inicializa lista de candidatos
    for (No* no : grafoInicial->lista_adj) {
        float heuristica = no->peso / no->arestas.size();
        Listacandidatos.emplace(make_tuple(heuristica, no->id));
    }

    while (!Listacandidatos.empty() && conjuntoSolucao->lista_adj.size() < grafoInicial->lista_adj.size()) {
        // Cria lista restrita de candidatos (RCL)
        vector<tuple<float, char>> rcl;
        priority_queue tempQueue = Listacandidatos; // Cópia temporária auxiliar

        // Determina quantos candidatos considerar (top alpha%)
        int rclSize = max(1, static_cast<int>(alpha * Listacandidatos.size()));

        // Preenche RCL
        for (int i = 0; i < rclSize && !tempQueue.empty(); ++i) {
            rcl.push_back(tempQueue.top());
            tempQueue.pop();
        }

        // Seleciona aleatoriamente da RCL
        int indiceAleatorio = rand() % rcl.size();
        auto noSelecionado = rcl[indiceAleatorio];
        char idNoSelecionado = get<1>(noSelecionado);

        // Remove o selecionado da fila original
        priority_queue<tuple<float, char>, vector<tuple<float, char>>, greater<tuple<float, char>>> newQueue; //cria uma nova fila
        bool removed = false; //flag de remoção
        while (!Listacandidatos.empty()) {
            auto current = Listacandidatos.top(); //pega o elemento do topo da fila
            if (!removed && get<1>(current) == idNoSelecionado) { //verifica se é o elemento selecionado e se ele não foi removido ainda
                Listacandidatos.pop(); // remove o elemento selecionado da lista de candidatos
                removed = true; // marca que o elemento foi removido
                continue;
            }
            newQueue.push(current); // adiciona o elemento atual na nova fila
            Listacandidatos.pop(); // remove o elemento atual da fila original
        }
        Listacandidatos = newQueue; // atualiza a fila de candidatos

        // Processa o nó selecionado
        No* selectedNo = grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(idNoSelecionado)];

        // Insere nó dominante
        conjuntoSolucao->inserirNosComDominancia(selectedNo->id, selectedNo->peso, true);

        // Processa vizinhos
        for (Aresta* aresta : selectedNo->arestas) {
            if (!conjuntoSolucao->verificaExistenciaNo(aresta->id_no_alvo)) {
                No* noAlvo = grafoInicial->lista_adj[grafoInicial->encontraIndiceNo(aresta->id_no_alvo)];
                conjuntoSolucao->inserirNosComDominancia(noAlvo->id, noAlvo->peso, false);

                // Mantém conectividade
                conjuntoSolucao->processarArestaIda(selectedNo->id, noAlvo->id, noAlvo->peso);
                conjuntoSolucao->processarArestaVolta(noAlvo->id, selectedNo->id, noAlvo->peso);
            }
        }

        // Atualiza pesos dos candidatos restantes
        reCalculaPesoNoCandidatoGuloso(&Listacandidatos, conjuntoSolucao, grafoInicial);
    }
}

void MinWeightDominatingSet::gulosoRandAdapt(Grafo *grafoInicial) {
    vector<float> LA = {0.2f, 0.5f, 0.8f};
    int numAlpha = LA.size();

    // Inicialização das probabilidades, qualidades e contadores
    vector<float> P(numAlpha, 1.0f / numAlpha); // Probabilidades iniciais
    vector<float> M(numAlpha, 0.0f);            // Soma das qualidades
    vector<int> m(numAlpha, 0);                  // Número de usos

    // Configurações
    int numIteracao = 300;
    int bloco = 40;

    Grafo* melhorSolucao = nullptr;
    float custo_best = FLT_MAX;

    for (int i = 1; i <= numIteracao; i++) {
        //escolhe alpha
        float r = static_cast<float>(rand()) / RAND_MAX;
        int idxAlpha = 0;
        float acumulado = 0.0f;
        for (int j = 0; j < numAlpha; j++) {
            acumulado += P[j];
            if (r <= acumulado) {
                idxAlpha = j;
                break;
            }
        }
        float alphaEscolhido = LA[idxAlpha];

        //chama guloso rand c alpha definio
        Grafo* solucaoAtual = new Grafo(grafoInicial->in_direcionado, grafoInicial->in_ponderado_aresta, grafoInicial->in_ponderado_vertice);
        this->conjuntoSolucao = solucaoAtual;
        this->gulosoRand(grafoInicial, alphaEscolhido);

        //calcula custo da solução atual
        float custo_S = 0.0f;
        for (No* no : this->conjuntoSolucao->lista_adj) {
            if (no->isDominante) {
                custo_S += no->peso;
            }
        }

        //att estatísticas
        float qualidade = 1.0f / custo_S;
        m[idxAlpha] += 1;
        M[idxAlpha] += qualidade;

        //att mlehor solucao de todas
        if (custo_S < custo_best) {
            custo_best = custo_S;
            if (melhorSolucao) delete melhorSolucao;
            melhorSolucao = new Grafo(*this->conjuntoSolucao); // cópia profunda
        }

        //att prob
        if (i % bloco == 0) {
            float somaQualidade = 0.0f;
            for (int j = 0; j < numAlpha; j++) {
                if (m[j] > 0) {
                    somaQualidade += (M[j]/m[j]);
                }
            }
            for (int j = 0; j < numAlpha; j++) {
                if (m[j] > 0) {
                    P[j] = (M[j]/m[j]) /somaQualidade;
                }
            }
        }
    }

    // Define o melhor conjunto como solução final
    delete this->conjuntoSolucao;
    this->conjuntoSolucao = melhorSolucao;
}


void MinWeightDominatingSet::impressao() {
    cout << "Vértices Dominantes: " << endl;
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



