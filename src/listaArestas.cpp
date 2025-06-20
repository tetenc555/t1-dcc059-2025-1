//
// Created by Bebs Fiorillo on 18/06/25.
//

#include "listaArestas.h"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

listaArestas::listaArestas(vector<No *> lista_adj, bool ehDir) {
    int qtdNos = lista_adj.size();
    for(int i=0;i<qtdNos;i++) {
        No* no = lista_adj[i];
        int qtdArestas = no->arestas.size();
        for (int j=0;j<qtdArestas;j++) {
            char ida = no->id;
            char volta = no->arestas[j]->id_no_alvo;
            tuple <char,char> conexao {ida,volta};
            conexoes.push_back(conexao);
            if (!(ehDir)) {
                tuple <char,char> conexaoVolta {volta,ida};
                conexoes.push_back(conexaoVolta);
            }
        }
    }
}

void listaArestas::imprimeArestas() {
    cout << "Lista de Arestas: {";
    for (int i = 0; i < conexoes.size(); i++) {
        cout << "(" << get<0>(conexoes[i]) << "," << get<1>(conexoes[i]) << ")" << endl;
    }
}

