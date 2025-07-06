//
// Created by Rafael on 28/05/2025.
//

#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include "listaArestas.h"


using namespace std;
class Grafo {

private:
    unordered_map<char, int> indiceNos;
    vector<vector<int>> distFloyd;
    vector<vector<int>> proxNo;
    bool floydPronto = false;
    unordered_map<char, char> pais;

public:
    Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice, int ordem);

    Grafo(bool direcionado, bool ehPondAresta, bool ehPondVertice);

    ~Grafo();

    void inserirNos(char id, int pesoNo);

    void criaListaArestas();

    void imprimirNos();

    int encontraIndiceNo(char idNo);

    void processarArestaIda(char idOrigem, char idAlvoAresta, int peso);

    void processarArestaVolta(char idAlvo, char idOrigem, int peso);

    bool verificaExistenciaNo(char idNo);

    vector<char> fecho_transitivo_direto(char id_no); // a
    vector<char> fecho_transitivo_indireto(char id_no); // b
    vector<char> caminho_minimo_dijkstra(char id_no_a, char id_no_b); // c
    vector<char> caminho_minimo_floyd(char id_no, char id_no_b); // d
    Grafo* arvore_geradora_minima_prim(const vector<char>& ids_nos); // e
    Grafo* arvore_geradora_minima_kruskal(const vector<char>& ids_nos); // f
    Grafo* arvore_caminhamento_profundidade(char id_no); // g
    Grafo* criaSubGrafoVerticeInduzido(const vector <char>& ids_nos);
    void buscaProfundidadeAux(No *atual, Grafo *arvore);
    vector<vector<int>> calcularMatrizDistancias();

    void imprimirGrafo(); // h
    void imprimirFormato();

    vector<int> calcularExcentricidades(); //h 0
    static int raio(const vector <int> &excentricidade); // h 1
    static int diametro(const vector <int> &excentricidade); // h 2
    vector<char> calculoCentroPeriferia(const vector <int> &excentricidade,int valorComparar); // h 3 e 4
    //vector<char> vertices_de_articulacao(vector <int> excentricidade); // i
    void salvarGrafoEmArquivo(const std::string &caminhoArquivo);



    int ordem;
    bool in_direcionado;
    bool in_ponderado_aresta;
    bool in_ponderado_vertice;
    vector<No*> lista_adj;
    listaArestas* lista_arestas = nullptr;

    char find(char x);
    void union_sets(char a, char b);
};



#endif //GRAFO_H
