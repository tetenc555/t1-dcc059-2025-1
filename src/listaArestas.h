//
// Created by Bebs Fiorillo on 18/06/25.
//

#ifndef LISTAARESTAS_H
#define LISTAARESTAS_H
#include "No.h"


class listaArestas {
public:
    listaArestas(vector<No*> lista_adj);
    ~listaArestas();

    vector<tuple<char,char>> conexoes;
    void imprimeArestas();
    bool contemConexao(char idOrigem, char idAlvo);
};



#endif //LISTAARESTAS_H
