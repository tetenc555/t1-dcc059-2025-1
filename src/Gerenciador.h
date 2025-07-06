#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <iostream>
#include "Grafo.h"

using namespace std;
class Gerenciador {
public:
    static void comandos(Grafo* grafo);
    static char get_id_entrada();
    static vector<char> get_conjunto_ids(const Grafo* grafo, const int& tam);
    static bool pergunta_imprimir_arquivo(const string& nome_arquivo);

    static void mudarArquivoTeste();
};


#endif //GERENCIADOR_H
