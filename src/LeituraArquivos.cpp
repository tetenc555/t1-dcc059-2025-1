//
// Created by Isabela on 25/06/2025.
//

#include "LeituraArquivos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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
    cout << " Direcionado: " << direcionado << endl;
    cout << " Ponderado: " << ponderadoAresta << endl;
    cout << " Ponderado Vertice: " << ponderadoVertice << endl;

    //lê a ordem
    int ordem = 0;
    if (getline(arquivo, linha)) {
        ordem = stoi(linha);
    }
    cout << "Numero de vertices: " << ordem << endl;

    Grafo* grafo = new Grafo(direcionado, ponderadoAresta, ponderadoVertice, ordem);

    //lê os vertices
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
        }
    }

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

        grafo->processarArestaIda(idA, idB, peso);

        if (!direcionado && idA != idB) {
            grafo->processarArestaVolta(idB, idA, peso);
        }
    }

    grafo->criaListaArestas();
    arquivo.close();
    return grafo;
}