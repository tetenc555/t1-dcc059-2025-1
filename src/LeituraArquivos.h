//
// Created by Isabela on 25/06/2025.
//

#ifndef LEITURAARQUIVOS_H
#define LEITURAARQUIVOS_H
#include  "Grafo.h"
#include  <string>

using namespace std;

class LeituraArquivos {
    public:
        static Grafo* lerGrafodoArquivo(const string &caminhoArquivo);
};

#endif //LEITURAARQUIVOS_H
