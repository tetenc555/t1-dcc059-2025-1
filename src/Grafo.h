//
// Created by Rafael on 28/05/2025.
//

#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include "listaArestas.h"


using namespace std;
class Grafo {

private:
    unordered_map<char, int> indiceNos;
    vector<vector<int>> distFloyd;
    bool floydPronto = false;

public:
    Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice, int ordem);
    ~Grafo();

    void inserirNos(char id, int pesoNo);

    void criaListaArestas();

    void imprimirNos();

    int encontraIndiceNo(char idNo);

    void processarArestaIda(int idOrigem, char idAlvoAresta, int peso);

    void processarArestaVolta(char idAlvo, char idOrigem, int peso);

    bool verificaExistenciaNo(char idNo);

    vector<char> fecho_transitivo_direto(char id_no); // a
    vector<char> fecho_transitivo_indireto(char id_no); // b
    vector<char> caminho_minimo_dijkstra(char id_no_a, char id_no_b); // c
    vector<char> caminho_minimo_floyd(char id_no, char id_no_b); // d
    Grafo* arvore_geradora_minima_prim(vector<char> ids_nos); // e
    Grafo* arvore_geradora_minima_kruskal(vector<char> ids_nos); // f
    Grafo* arvore_caminhamento_profundidade(char id_no); // g
    void imprimirGrafo(); // h
    int raio(); // h 1
    int diametro(); // h 2
    vector<char> centro(); // h 3
    vector<char> periferia(); // h 4
    vector<char> vertices_de_articulacao(); // i


    int ordem;
    bool in_direcionado;
    bool in_ponderado_aresta;
    bool in_ponderado_vertice;
    vector<No*> lista_adj;
    listaArestas* lista_arestas = nullptr;
};



#endif //GRAFO_H
