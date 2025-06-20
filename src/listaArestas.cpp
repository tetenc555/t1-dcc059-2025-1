//
// Created by Bebs Fiorillo on 18/06/25.
//

#include "listaArestas.h"
#include <iostream>
#include <vector>
using namespace std;

listaArestas::listaArestas(vector<No *> lista_adj, bool ehDir) {
    for(int i=0;i<lista_adj.size();i++) {
        No* no = lista_adj[i];
        for (int j=0;j<no->arestas.size();j++) {
            tuple <char,char> conexao = {no->id,no->arestas[j]};
            conexoes.push_back(conexao);
            if (!(ehDir)) {
                tuple <char,char> conexaoVolta = {no->arestas[j],no->id};
                conexoes.push_back(conexaoVolta);
            }
        }
    }
}
