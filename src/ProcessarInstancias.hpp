#ifndef TRB_GRAFOS_PROCESSARINSTANCIAS_HPP
#define TRB_GRAFOS_PROCESSARINSTANCIAS_HPP

#include <vector>
#include <string>
#include <chrono>
#include "Grafo.h"

using namespace std;

struct ResultadoInstancia {

    //informacoe basicas
    string nome;
    int numVertices;
    float bestSolucao;

    //melhores resultados
    float guloso;
    float randomizadoAlpha02;
    float randomizadoAlpha03;
    float randomizadoAlpha04;

    //tempo
    double guloso_tempo;
    double randomizadoAlpha02_tempo;
    double randomizadoAlpha03_tempo;
    double randomizadoAlpha04_tempo;

};

void processarInstanciasComparativo(const string& arquivoLista);

#endif //TRB_GRAFOS_PROCESSARINSTANCIAS_HPP