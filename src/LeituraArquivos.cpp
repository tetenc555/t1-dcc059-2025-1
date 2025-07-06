#include "LeituraArquivos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace std;
Grafo* LeituraArquivos::lerGrafodoArquivo(const string &caminhoArquivo) {
    ifstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir arquivo " + caminhoArquivo);
    }

    string linha;
    //lê se o grafo é direcionado, ponderado na aresta ou no vertice
    bool direcionado, ponderadoAresta, ponderadoVertice;
    if (getline(arquivo, linha)) {
        istringstream iss(linha);
        int d, pa, pv;
        iss >> d >> pa >> pv;
        direcionado = (d == 1);
        ponderadoAresta = (pa == 1);
        ponderadoVertice = (pv == 1);
    }

    //lê a ordem
    int ordem = 0;
    if (getline(arquivo, linha)) {
        ordem = stoi(linha);
    }

    Grafo* grafo = new Grafo(direcionado, ponderadoAresta, ponderadoVertice);
    grafo->lista_adj.reserve(ordem); //pré-alocação para a lista de adjacencias

    // Pré-alocação de memória para vértices
    unordered_map<char, int> mapaVertices;
    mapaVertices.reserve(ordem);

    // Lê vértices
    for (int i = 0; i < ordem; i++) {
        if (getline(arquivo, linha)) {
            istringstream iss(linha);
            char id;
            int peso = -1;
            if (ponderadoVertice) {
                iss >> id >> peso;
            }
            else {
                iss >> id;
            }
            grafo->inserirNos(id, peso);
            mapaVertices[id] = i;  // Mapeia ID para índice
        }
    }

    // Lê arestas
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        char idA, idB;
        int peso = 0;

        if (ponderadoAresta) {
            iss >> idA >> idB >> peso;
        }
        else {
            iss >> idA >> idB;
        }

        // Processa aresta
        grafo->processarArestaIda(idA, idB, peso);

        // Se não direcionado e não for loop, processa volta
        if (!direcionado && idA != idB) {
            grafo->processarArestaVolta(idB, idA, peso);
        }
    }

    grafo->criaListaArestas();
    arquivo.close();
    return grafo;
}

void Grafo::salvarGrafoEmArquivo(const string& caminhoArquivo) { //É O FORMATO DE LISTA DE ADJACENCIAS, SE FOR ALTERAR O FORMATO DA IMPRESSÃO TEM Q FAZER OUTRA FUNÇÃO
    ofstream arquivo(caminhoArquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao criar arquivo " + caminhoArquivo);
    }

    // Escreve cabeçalho (direcionado, ponderado aresta, ponderado vértice)
    arquivo << (this->in_direcionado ? 1 : 0) << " "
            << (this->in_ponderado_aresta ? 1 : 0) << " "
            << (this->in_ponderado_vertice ? 1 : 0) << "\n";

    // Escreve a ordem do grafo
    arquivo << lista_adj.size() << "\n";

    // Escreve cada nó e suas adjacências
    for (int i = 0; i < lista_adj.size(); i++) {
        arquivo << lista_adj[i]->id;

        // Adiciona peso do vértice se for ponderado
        if (this->in_ponderado_vertice) {
            arquivo << " (" << lista_adj[i]->peso << ")";
        }

        // Adiciona as arestas
        if (!lista_adj[i]->arestas.empty()) {
            arquivo << ": ";
            for (size_t j = 0; j < lista_adj[i]->arestas.size(); j++) {
                arquivo << lista_adj[i]->arestas[j]->id_no_alvo;

                // Adiciona peso da aresta se for ponderado
                if (this->in_ponderado_aresta) {
                    arquivo << "(" << lista_adj[i]->arestas[j]->peso << ")";
                }

                // Adiciona separador se não for a última aresta
                if (j != lista_adj[i]->arestas.size() - 1) {
                    arquivo << " -> ";
                }
            }
        }
        arquivo << endl;
    }

    arquivo.close();
}