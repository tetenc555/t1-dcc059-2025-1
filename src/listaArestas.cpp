//
// Created by Bebs Fiorillo on 18/06/25.
//

#include "listaArestas.h"
#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

listaArestas::listaArestas(vector<No *> lista_adj) {
    int qtdNos = lista_adj.size();
    for(int i=0;i<qtdNos;i++) {
        No* no = lista_adj[i];
        int qtdArestas = no->arestas.size();
        for (int j=0;j<qtdArestas;j++) {
            char ida = no->id;
            char volta = no->arestas[j]->id_no_alvo;
            tuple <char,char> conexao {ida,volta};
            conexoes.push_back(conexao);
        }
    }
}

listaArestas::~listaArestas() = default;


void listaArestas::imprimeArestas() {
    cout << "Lista de Arestas: {";
    int tamanho = conexoes.size();
    for (int i = 0; i < tamanho; i++) {
        cout << "(" << get<0>(conexoes[i]) << "," << get<1>(conexoes[i]) << ") ,";
    }
    cout << "}" << endl;
}

bool listaArestas::contemConexao(char idOrigem, char idAlvo) {
    for (tuple conexao : this->conexoes) {
        if (idOrigem == get<0>(conexao) && idAlvo == get<1>(conexao)) {
            return true;
        }
    }
    return false;
}

